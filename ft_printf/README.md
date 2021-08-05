# ft_printf project

  Little project with pretty optimized integer convertions and really slow (my fault) long arifmetics for floats.

## Goal:
  Create own printf with most of flags and specifiers, but without buffer managment.


## Result:

  Supported specifiers:
  
* integers:
  - %d
  - %i
  - %u
  - %x
  - %X
  - %p
* text:
  - %c
  - %s
* floats:
  - %f
  - %e
* util:
  - %n

  and supported flags:
  
| Flag        | Description                                           |
| ----------- | ----------------------------------------------------- |
| -         | left-justify                                          |
| +         | force sign print                                      |
| \<space\> | blank space substitute '+' sign for positive numbers  |
| #         | alternative form                                      |
| 0         | left-pads the number with zeroes (0)                  |
| \<num\>   | width parameter                                       |
| \*        | take width from next argument                         |
| .\<num\>  | percision                                             |
| .\*       | take precision from next argument                     |



## Usage

| makefile rule  | Description                                           |
| -------------- | ----------------------------------------------------- |
|  all           | compiles static lib libftprintf.a                     |
|  debug         | compiles libftprintf.a + debug a.out program with some tests |

./a.out output:
```
orig: [   10]  [returned : 13]
ft:   [   10]  [returned : 13]

orig: [hello world!]  [returned : 20]
ft:   [hello world!]  [returned : 20]

orig: [hello wor      ]  [returned : 23]
ft:   [hello wor      ]  [returned : 23]

orig: [               10.123000000000]  [returned : 38]
ft:   [               10.123000000000]  [returned : 38]

orig: [  1.012300000000e+01]  [returned : 28]
ft:   [  1.012300000000e+01]  [returned : 28]

orig: [0x556a98c390ce]  [returned : 22]
ft:   [0x556a98c390ce]  [returned : 22]
```
