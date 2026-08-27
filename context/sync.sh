#!/usr/bin/env bash

set -euo pipefail

repo="$(gh repo view --json nameWithOwner --jq '.nameWithOwner')"
repo_url="https://github.com/${repo}"
context_dir="$(cd "$(dirname "$0")" && pwd)"
work_dir="$(mktemp -d "${TMPDIR:-/tmp}/khal-github-context.XXXXXX")"

cleanup() {
  rm -rf "$work_dir"
}
trap cleanup EXIT

mkdir -p "$work_dir/issues" "$work_dir/wiki/pages"

gh issue list \
  --repo "$repo" \
  --state all \
  --limit 10000 \
  --json number,title,body,state,stateReason,url,author,assignees,labels,milestone,comments,createdAt,updatedAt,closedAt,closedByPullRequestsReferences \
  | jq 'sort_by(.number)' > "$work_dir/issues/issues.json"

issue_count="$(jq 'length' "$work_dir/issues/issues.json")"
generated_at="$(date -u +'%Y-%m-%dT%H:%M:%SZ')"

{
  printf '# GitHub Issues\n\n'
  printf 'Локальный снимок тикетов [%s](%s/issues).\n\n' "$repo" "$repo_url"
  printf -- '- Обновлено: `%s`\n' "$generated_at"
  printf -- '- Количество: `%s`\n\n' "$issue_count"
  printf '## Тикеты\n\n'
  jq -r '.[] | "- [#\(.number): \(.title)](issue-\(.number).md) — `\(.state)`"' "$work_dir/issues/issues.json"
  printf '\nДля машинной обработки используйте [`issues.json`](issues.json).\n'
} > "$work_dir/issues/README.md"

while IFS= read -r number; do
  jq -r --argjson number "$number" '
    .[] | select(.number == $number) |
    def text_or_dash: if . == null or . == "" then "—" else . end;
    def people: if length == 0 then "—" else map(.login) | join(", ") end;
    def label_names: if length == 0 then "—" else map(.name) | join(", ") end;
    "# #\(.number): \(.title)\n\n" +
    "- Статус: `\(.state)`\n" +
    "- Причина состояния: \(.stateReason | text_or_dash)\n" +
    "- Автор: \(.author.login // "—")\n" +
    "- Исполнители: \(.assignees | people)\n" +
    "- Метки: \(.labels | label_names)\n" +
    "- Создан: `\(.createdAt)`\n" +
    "- Обновлён: `\(.updatedAt)`\n" +
    "- Закрыт: \(.closedAt | text_or_dash)\n" +
    "- GitHub: \(.url)\n" +
    (if .milestone == null then "- Веха: —\n"
     else "- Веха: #\(.milestone.number) — \(.milestone.title)\n" end) +
    "\n## Описание\n\n" +
    ((.body // "") | if . == "" then "_Описание отсутствует._" else . end) + "\n" +
    (if .milestone == null then ""
     else "\n## Веха\n\n### \(.milestone.title)\n\n" +
       ((.milestone.description // "") | if . == "" then "_Описание отсутствует._" else . end) +
       "\n\nСрок: " + ((.milestone.dueOn // "—") | tostring) + "\n"
     end) +
    "\n## Комментарии (\(.comments | length))\n\n" +
    (if (.comments | length) == 0 then "_Комментариев нет._\n"
     else (.comments | map(
       "### \(.author.login // "—") — \(.createdAt)\n\n" +
       ((.body // "") | if . == "" then "_Пустой комментарий._" else . end) + "\n"
     ) | join("\n"))
     end) +
    "\n## Связанные закрывающие Pull Requests\n\n" +
    (if (.closedByPullRequestsReferences | length) == 0 then "_Нет._\n"
     else (.closedByPullRequestsReferences | map("- #\(.number): [\(.title)](\(.url))") | join("\n")) + "\n"
     end)
  ' "$work_dir/issues/issues.json" > "$work_dir/issues/issue-${number}.md"
done < <(jq -r '.[].number' "$work_dir/issues/issues.json")

wiki_repo="https://github.com/${repo}.wiki.git"
wiki_clone="$work_dir/wiki-repo"

if git clone --quiet --depth 1 "$wiki_repo" "$wiki_clone"; then
  wiki_commit="$(git -C "$wiki_clone" rev-parse HEAD)"
  wiki_updated_at="$(git -C "$wiki_clone" show -s --format=%cI HEAD)"
  : > "$work_dir/wiki/pages.ndjson"

  while IFS= read -r page; do
    mkdir -p "$work_dir/wiki/pages/$(dirname "$page")"
    cp "$wiki_clone/$page" "$work_dir/wiki/pages/$page"
    title="$(basename "$page")"
    title="${title%.*}"
    jq -n \
      --arg path "$page" \
      --arg title "$title" \
      --rawfile content "$wiki_clone/$page" \
      '{path: $path, title: $title, content: $content}' \
      >> "$work_dir/wiki/pages.ndjson"
  done < <(git -C "$wiki_clone" ls-files)

  jq -s \
    --arg repository "$repo" \
    --arg url "${repo_url}/wiki" \
    --arg commit "$wiki_commit" \
    --arg updatedAt "$wiki_updated_at" \
    '{repository: $repository, url: $url, commit: $commit, updatedAt: $updatedAt, pages: .}' \
    "$work_dir/wiki/pages.ndjson" > "$work_dir/wiki/wiki.json"

  wiki_count="$(jq '.pages | length' "$work_dir/wiki/wiki.json")"
  {
    printf '# GitHub Wiki\n\n'
    printf 'Локальный снимок Wiki [%s](%s/wiki).\n\n' "$repo" "$repo_url"
    printf -- '- Коммит Wiki: `%s`\n' "$wiki_commit"
    printf -- '- Обновлено в Wiki: `%s`\n' "$wiki_updated_at"
    printf -- '- Страниц и служебных файлов: `%s`\n\n' "$wiki_count"
    printf '## Файлы\n\n'
    jq -r '.pages[] | "- [\(.path)](pages/\(.path))"' "$work_dir/wiki/wiki.json"
    printf '\nПолное содержимое страниц также находится в [`wiki.json`](wiki.json).\n'
  } > "$work_dir/wiki/README.md"
else
  jq -n \
    --arg repository "$repo" \
    --arg url "${repo_url}/wiki" \
    '{repository: $repository, url: $url, commit: null, updatedAt: null, pages: []}' \
    > "$work_dir/wiki/wiki.json"
  printf '# GitHub Wiki\n\nWiki пока не содержит страниц.\n' > "$work_dir/wiki/README.md"
fi

rm -f "$work_dir/wiki/pages.ndjson"

rm -rf "$context_dir/issues" "$context_dir/wiki"
mv "$work_dir/issues" "$context_dir/issues"
mv "$work_dir/wiki" "$context_dir/wiki"

printf 'Синхронизировано: %s Issues, Wiki — %s файлов.\n' \
  "$issue_count" \
  "$(jq '.pages | length' "$context_dir/wiki/wiki.json")"
