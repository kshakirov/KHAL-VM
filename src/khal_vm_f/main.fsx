// Наш единственный опкод
let OP_PRINT = 0x0A

// Симулируем память строк ВМ
let stringPool = [| "Привет, мир! (KHAL-VM F#)" |]

// Блоки памяти ВМ (Регистры и указатель команд)
let registers = Array.zeroCreate<int> 256
let mutable IP = 0

// Наш байт-код: команда PRINT, которая должна прочитать строку по индексу из R0
// Упакуем её в массив инструкций (Opcode, RegIndex)
let bytecode = [| (OP_PRINT, 0) |]

// Загружаем в R0 индекс строки из пула (строка 0)
registers.[0] <- 0

printfn "[LAUNCH] 📡 KHAL-VM (F#) активирована в изолированной среде."

// Главный цикл интерпретатора (пока на 1 шаг)
while IP < bytecode.Length do
    let opcode, regIdx = bytecode.[IP]
    if opcode = OP_PRINT then
        let stringIndex = registers.[regIdx]
        printfn "[VM OUTPUT] 🖖 %s" stringPool.[stringIndex]
    IP <- IP + 1

printfn "[READY]  🔋 Выполнение завершено. IP = 0x%02X." IP
