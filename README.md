# Graph KHAL

[English](#english) | [Русский](#русский)

## English

An experimental graph-based computing machine founded on combinatory logic and local graph transformations.

### Research Subject

Computation is considered a sequence of structural graph transformations.

A program is represented as an application graph. A computational automaton traverses the graph and applies reduction rules.

### Computational Model

- The graph is physically represented in memory.
- Nodes have a fixed size and are addressed by indices.
- A cursor moves along graph edges.
- Reduction rules define graph transformations.
- Evaluation order is governed by the semantics of reduction rules.

The computational model is based on SKI combinatory logic extended with machine primitives.

### Research Directions

- Graph reduction.
- Arithmetic and logical operations.
- Control structures.
- Recursion.
- State representation.
- Mapping programming language semantics onto the graph-based computational model.

### Research Method

Each computational property is investigated through an individual executable study.

The C++ implementation serves as an experimental model of the graph automaton.

### Objective

To investigate a computing machine in which the structure of a program is itself its execution space, and computation is performed by transforming that structure.

---

## Русский

Исследовательская графовая вычислительная машина на основе комбинаторной логики и локальных преобразований графа.

### Предмет исследования

Вычисление рассматривается как последовательное изменение структуры графа.

Программа представляется графом применений, а вычислительный автомат перемещается по нему и выполняет правила редукции.

### Вычислительная модель

- Граф физически представлен в памяти.
- Узлы имеют фиксированный размер и адресуются индексами.
- Курсор перемещается по связям графа.
- Правила редукции определяют преобразования графа.
- Порядок вычисления определяется семантикой правил редукции.

Базис вычислительной модели — комбинаторная логика SKI, дополненная машинными примитивами.

### Направления исследования

- Графовая редукция.
- Арифметические и логические операции.
- Управляющие структуры.
- Рекурсия.
- Представление состояния.
- Отображение семантики языков программирования на графовую вычислительную модель.

### Метод исследования

Каждое вычислительное свойство исследуется посредством отдельного исполняемого этюда.

Реализация на C++ служит экспериментальной моделью графового автомата.

### Цель

Исследовать возможность построения вычислительной машины, в которой структура программы одновременно является пространством её исполнения, а вычисление осуществляется преобразованием этой структуры.
