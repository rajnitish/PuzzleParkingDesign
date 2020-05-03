# PuzzleParkingDesign
<pre>
|-----+-----+-----+-----+-----+-----|
| 01  | 06  | 11  | 16  |  21 |     |
|-----+-----+-----+-----+-----+-----|
| 02  |  07 |  12 |  17 |  22 |     |
|-----+-----+-----+-----+-----+-----|
|  03 | 08  |  13 |  18 |  23 |     |
|-----+-----+-----+-----+-----+-----|
|  04 | 09  |  14 |  19 |  24 |     |
|-----+-----+-----+-----+-----+-----|
|  05 | 10  |  15 |  20 |  25 |     |
|-----+-----+-----+-----+-----+-----|
|     |     |     |     |     |     |
|-----+-----+-----+-----+-----+-----|
</pre>
Above is layout of automatic parking system. A car can placed in any of the slot except in bottom row. Since botton row represent Bay Area.
The idea is that whenver car is retrieved the car below in the same column will be moved to left or right depending upon empty space available
.At any moment, In any of the row, there will be one empty space at least, this is due to shift and pushdown car.
