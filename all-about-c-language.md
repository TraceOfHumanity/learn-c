
## Ключові слова

Кількість залежить від версії стандарту: C89 — 32, C99 — 37 (+ `inline`, `restrict`, `_Bool`, `_Complex`, `_Imaginary`), C11 — 44 (+ `_Alignas`, `_Alignof`, `_Atomic`, `_Generic`, `_Noreturn`, `_Static_assert`, `_Thread_local`).

Базові 32 (C89), які реально використовуються в коді:

```
auto      break     case      char      const     continue
default   do        double    else      enum      extern
float     for       goto      if        int       long
register  return    short     signed    sizeof    static
struct    switch    typedef   union     unsigned  void
volatile  while
```

Решта ключових слів з C99/C11 (`_Bool`, `_Atomic` тощо) використовуються рідко — зазвичай замість них беруть зручні макроси з `<stdbool.h>` (`bool`, `true`, `false`).

## Компіляція проєкту
Використовуючи термінал перейди в папку де лежить`main.c` та введи команду
`clang -Wall -Wextra -Wpedantic -g main.c -o program`
- `main.c` — твій вихідний файл
- `-o program` — назва виконуваного файлу (output). Можеш назвати як завгодно
- `-g` — додає debug-інформацію (потрібна для нормальних повідомлень від sanitizers)

Запусти: `./program` або за один прохід `clang -Wall -Wextra -g main.c -o program && ./program` 

Якщо програма вихідний код міститься у кількох файлах то для компіляції їх потрібно просто перерахувати `clang -Wall -Wextra -g main.c other.c -o program`. `.h` файли **не вказуєш** — вони підключаються автоматично через `#include` всередині `.c` файлів.

Щоб дізнатися час виконання програми, виконай `time ./program`
Якщо хочеш знати не весь час програми, а скільки займає конкретна функція або цикл — вимірюй зсередини:

```c
#include <stdio.h>#include <time.h>
int main(void) {    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // тут твій код який хочеш заміряти    long sum = 0;    for (int i = 0; i < 1000000000; i++) {        sum += i;    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +                     (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("sum = %ld\n", sum);    printf("time: %.6f seconds\n", elapsed);
    return 0;}
```

`CLOCK_MONOTONIC` — годинник який не стрибає (не залежить від зміни системного часу). Точність — наносекунди.

Для пергляду ассемблера, який генерується з програми використати `gcc -S -O0 main.c -o main.asm`

## Специфікатори формату (printf/scanf)

Специфікатори кажуть `printf`/`scanf`, як інтерпретувати байти аргументу — без них немає способу дізнатись, чи це `int`, `float` чи рядок.

```
%d, %i   — цілий зі знаком (int)
%u       — цілий без знаку (unsigned int)
%o       — вісімкове число (без знаку)
%x, %X   — шістнадцяткове число (мал./вел. літери)
%f       — дійсне число з крапкою (double)
%e, %E   — наукова нотація (1.5e+03)
%g, %G   — коротший з варіантів %f / %e
%c       — один символ
%s       — рядок (char*, до '\0')
%p       — вказівник (адреса)
%%       — символ % (не приймає аргумент)
```

### Модифікатори довжини

Ставляться перед літерою типу, змінюють розмір очікуваного аргументу.

```
hh — char       (%hhd)
h  — short      (%hd)
l  — long       (%ld, %lu) ; для scanf %lf = double
ll — long long  (%lld, %llu)
L  — long double(%Lf)
z  — size_t     (%zu)  — правильний специфікатор для sizeof(...)
```

**Важливо:** у `printf` для `%f` подавати `double` (int/float самі підвищуються до double за замовчуванням), а у `scanf` для `double` потрібно `%lf`, бо `scanf` приймає вказівник і підвищення аргументів там не працює.

```c
int a = 5;
double b = 3.14;
size_t n = sizeof(a);

printf("%d %f %zu\n", a, b, n);
scanf("%lf", &b); // саме %lf, а не %f
```

## stdio.h — введення/виведення

**Відкриття/закриття файлів**
- **`fopen`** — відкриває файл, повертає `FILE*` (вказівник на потік) або `NULL` при помилці
  `FILE *f = fopen("data.txt", "w");`
- **`fclose`** — закриває відкритий потік, звільняє ресурси і скидає буфер на диск
  `fclose(f);`

**Читання**
- **`scanf`** — читає з stdin за форматом
  `scanf("%d", &n);`
- **`fscanf`** — читає з файлу/потоку за форматом
  `fscanf(f, "%d", &n);`
- **`sscanf`** — читає з рядка в пам'яті за форматом
  `sscanf(buf, "%d", &n);`
- **`fgets`** — безпечно читає рядок з обмеженням довжини (заміна небезпечного `gets`, якого немає в C11+)
  `fgets(buf, sizeof(buf), f);`
- **`getchar`** — читає один символ зі stdin
  `int c = getchar();`
- **`fgetc` / `getc`** — читає один символ з потоку
  `int c = fgetc(f);`

**Виведення**
- **`printf`** — виводить форматований рядок у stdout (термінал)
  `printf("hello %d\n", 5);`
- **`sprintf`** — записує форматований рядок у буфер `char[]` замість екрана (без перевірки розміру буфера — небезпечно, краще `snprintf`)
  `sprintf(buf, "hello %d", 5);`
- **`fprintf`** — форматований вивід у файл або будь-який потік `FILE*` (в т.ч. `stdout`, `stderr`)
  `fprintf(f, "hello %d\n", 5);`
- **`puts`** — виводить рядок у stdout і додає `\n`
  `puts("hello");`
- **`fputs`** — виводить рядок у потік без автододавання `\n`
  `fputs("hello", f);`
- **`putchar`** — виводить один символ у stdout
  `putchar('A');`
- **`fputc` / `putc`** — виводить один символ у потік
  `fputc('A', f);`

**Позиціонування в файлі**
- **`fseek`** — переміщує позицію читання/запису в потоці
  `fseek(f, 0, SEEK_END);`
- **`ftell`** — повертає поточну позицію в потоці
  `long pos = ftell(f);`
- **`rewind`** — повертає позицію на початок файлу
  `rewind(f);`

**Помилки**
- **`feof`** — перевіряє, чи потік дійшов до кінця файлу (прапорець встановлюється **після** невдалої спроби читання, не до неї)
  `while (!feof(f)) { ... }` — зазвичай краще перевіряти результат самого читання (напр. `fgets`), а не `feof` напряму
- **`ferror`** — перевіряє, чи виникла помилка потоку
  `if (ferror(f)) { ... }`
- **`clearerr`** — скидає прапорці помилки/EOF потоку
  `clearerr(f);`
- **`perror`** — виводить у stderr системне повідомлення про останню помилку
  `perror("fopen failed");`

**Буферизація**
- **`fflush`** — примусово скидає буфер у файл/на екран (важливо перед `scanf` після `printf` без `\n`)
  `fflush(stdout);`
- **`setvbuf` / `setbuf`** — налаштовує тип буферизації потоку
  `setvbuf(f, NULL, _IOFBF, 1024);`

**Інше**
- **`remove`** — видаляє файл
  `remove("data.txt");`
- **`rename`** — перейменовує файл
  `rename("old.txt", "new.txt");`
- **`tmpfile`** — створює тимчасовий файл, який видаляється автоматично при закритті
  `FILE *tmp = tmpfile();`

```c
FILE *f = fopen("data.txt", "w");
if (f == NULL) {
    return 1; // помилка відкриття
}
fprintf(f, "число: %d\n", 42);
fclose(f);
```

## stdarg.h — функції зі змінною кількістю аргументів

Дозволяє писати функції з невідомою на етапі компіляції кількістю аргументів (як `printf`). Потрібен хоча б один звичайний (named) параметр перед `...` — він служить опорною точкою.

- **`va_list`** — тип для зберігання поточної позиції в списку аргументів
  `va_list parg;`
- **`va_start`** — ініціалізує `va_list`, приймає останній named-параметр як опорну точку
  `va_start(parg, v2);`
- **`va_arg`** — дістає наступний аргумент і зсуває позицію далі; тип вказуєш явно, компілятор довіряє тобі
  `double value = va_arg(parg, double);`
- **`va_end`** — завершує роботу зі списком аргументів, обов'язково перед `return`
  `va_end(parg);`
- **`va_copy`** *(з C99)* — копіює поточний стан `va_list` в інший, щоб пройти аргументи двічі (напр. власна реалізація `vprintf`); копія теж потребує свій `va_end`
  `va_list copy; va_copy(copy, parg); ... va_end(copy);`

Це весь `stdarg.h` — 1 тип + 4 макроси, більше в бібліотеці нічого немає.

**Важливо:**
- Компілятор не передає кількість аргументів — потрібен sentinel (напр. `0.0` як останній аргумент виклику) або окремий лічильник/формат-рядок (як у `printf`).
- Аргументи в `...` проходять **default argument promotions**: `float → double`, `char`/`short → int`. Тому для дробових у `va_arg` завжди пишеш `double`.
- Але **`int`/`long` до `double` не підвищуються автоматично** — якщо передати `int` без явного `(double)`, `va_arg(parg, double)` прочитає його біти як `double` → undefined behavior.
- Кожен `va_start`/`va_copy` має свою пару `va_end` — виклик `va_arg` після `va_end` без нового `va_start`/`va_copy` — undefined behavior.

```c
double avarage(double v1, double v2, ...) {
  va_list parg;
  double sum = v1 + v2;
  double value = 0.0;
  int count = 2;

  va_start(parg, v2);
  while ((value = va_arg(parg, double)) != 0.0) {
    sum += value;
    count++;
  }
  va_end(parg);

  return sum / count;
}

// виклик: останній аргумент — sentinel 0.0
avarage(v1, 3.5, v2, 4.5, 0.0);
// int/long передаємо через явний каст до double
avarage((double)num2, v2, (double)num1, (double)num4, (double)num3, 0.0);
```

