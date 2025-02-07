
# floor / tranc
正负数统一，a>>b 等于 a/2^b

```c
// a/b: s1.7
c = (a * b) >> 7      //s1.7
```

```verilog
wire signed [7:0] a, b;     // s1.7
wire signed [15:0] ab = a * b; // s2.14
wire signed [7:0] c = $signed(ab[14:7]);    //s1.7
```

# roundToInf
正负数不一致

```c
// a/b: s1.7
c = round(a * b / (1<<7));      //s1.7
```

```verilog
wire signed [7:0] a, b;     //s1.7
wire signed [15:0] ab = a * b; //s2.14

wire [15:0] ab_abs = ab >= 0 ? ab : -ab;
wire [6:0]  ab_abs_round = ab_abs[13:7] + ab_abs[6];

wire signed [7:0] c = ab >= 0 ? $signed(1'b0, ab_abs_round) : $signed(1'b1, -ab_abs_round);
```

