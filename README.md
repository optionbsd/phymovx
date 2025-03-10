# PhyMovX
<p align="center">
  <img src="logo.png" alt="PhyMovX Logo" width="400">
</p>
Альтернатива Core Physics. Симуляция физики для создания естественных анимаций

## CLI

Для запуска Phymovx используйте следующую команду:

```bash
build/phymovx -steps <steps> -duration <duration> -startpos <startpos> -endpos <endpos> [опции]
```

Где:

- `-steps <steps>`: Количество шагов для симуляции. Чем больше шагов, тем точнее результат. (Обязательно)
- `-duration <duration>`: Общая длительность симуляции. Можно указать с единицей измерения (например, `1s` для 1 секунды). (Обязательно)
- `-startpos <startpos>`: Начальная позиция объекта. (Обязательно)
- `-endpos <endpos>`: Конечная позиция объекта. (Обязательно)

### Опции командной строки

- `-steps <steps>`  
  Количество шагов для симуляции. Чем больше значеие, тем более детализированным будет результат. (Обязательно)

- `-duration <duration>`  
  Общая длительность симуляции. Можно указать единицу измерения времени (например, `1s` для 1 секунды). (Обязательно)

- `-startpos <startpos>`  
  Начальная позиция объекта. (Обязательно)

- `-endpos <endpos>`  
  Конечная позиция объекта. (Обязательно)

- `-gravity <gravity>`  
  Ускорение свободного падения (м/с²). Эта опция используется только в физической модели. Если используется easing, эта опция игнорируется.

- `-ease <ease-type>`  
  Тип функции easing для применения. Может быть одним из следующих значений:
  - `ease-in`
  - `ease-out`
  - `ease-in-out`
  
  Эта опция позволяет применить плавное изменение позиции между startpos и endpos. По умолчанию используется линейная интерполяция (без easing).

- `-easeparam <param>`  
  Параметр, определяющий силу функции easing. Это числовое значение, которое влияет на кривизну. По умолчанию используется значение `2.0`.

- `-output <json/css>`
  Вывести в формате JSON или CSS