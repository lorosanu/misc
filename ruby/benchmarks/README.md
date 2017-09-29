# Ruby benchmarks

## 2d_true_count (**each_count**)

Find out which 2D 'true' count method is the fastest
* each_count_method       `count=0; v.each{|sv| count += sv.count(true) }`
* inject_count_method_v1  `v.inject(0){|sum, sv| sum + sv.count(true) }`
* inject_count_method_v2  `v.inject(0){|sum, sv| sum + sv.count{|x| x } }`
* each_each_if_method     `v.each{|sv| sv.each{|item| count += 1 if item } }`
* times_times_if_method   `v.size.times{|i| v[i].size.times{|j| count += 1 if v[i][j] } }`
* flatten_count_method    `v.flatten.count(true)`

Performance order

```
each_count >~ inject_count_v1 >> inject_count_v2 > ...
```

Proof

```
Matrix=[10, 10]

Rehearsal ----------------------------------------------------------
each_count_method        0.000000   0.000000   0.000000 (  0.002388)
inject_count_method_v1   0.010000   0.000000   0.010000 (  0.003094)
inject_count_method_v2   0.000000   0.000000   0.000000 (  0.004916)
each_each_if_method      0.010000   0.000000   0.010000 (  0.005655)
times_times_if_method    0.010000   0.000000   0.010000 (  0.007458)
flatten_count_method     0.010000   0.000000   0.010000 (  0.007980)
------------------------------------------------- total: 0.040000sec

                             user     system      total        real
each_count_method        0.000000   0.000000   0.000000 (  0.002124)
inject_count_method_v1   0.000000   0.000000   0.000000 (  0.002585)
inject_count_method_v2   0.010000   0.000000   0.010000 (  0.004492)
each_each_if_method      0.000000   0.000000   0.000000 (  0.005212)
times_times_if_method    0.010000   0.000000   0.010000 (  0.006879)
flatten_count_method     0.010000   0.000000   0.010000 (  0.007373)

...

Matrix=[1000, 1000]

Rehearsal ----------------------------------------------------------
each_count_method       13.540000   0.000000  13.540000 ( 13.548190)
inject_count_method_v1  13.450000   0.000000  13.450000 ( 13.455943)
inject_count_method_v2  25.160000   0.000000  25.160000 ( 25.176630)
each_each_if_method     35.750000   0.000000  35.750000 ( 35.769219)
times_times_if_method   47.320000   0.000000  47.320000 ( 47.350218)
flatten_count_method    50.510000   0.910000  51.420000 ( 51.457130)
----------------------------------------------- total: 186.640000sec

                             user     system      total        real
each_count_method       13.390000   0.000000  13.390000 ( 13.390733)
inject_count_method_v1  13.630000   0.000000  13.630000 ( 13.635951)
inject_count_method_v2  25.090000   0.000000  25.090000 ( 25.105121)
each_each_if_method     36.390000   0.000000  36.390000 ( 36.409551)
times_times_if_method   47.600000   0.000000  47.600000 ( 47.631573)
flatten_count_method    50.570000   1.070000  51.640000 ( 51.668962)
```


## array_concat (**concat**)

Find out which array concatenation method is the fastest
* concat_method  `c = a.dup ; c.concat(b)`
* append_method  `c = a.dup ; b.each{|x| c << x }`
* push_method    `c = a.dup ; b.each{|x| c.push(x) }`

Performance order

```
concat >> append > push
```

Proof

```
N=10

Rehearsal -------------------------------------------------
concat_method   0.000000   0.000000   0.000000 (  0.000468)
append_method   0.000000   0.000000   0.000000 (  0.000815)
push_method     0.000000   0.000000   0.000000 (  0.000938)
---------------------------------------- total: 0.000000sec

                    user     system      total        real
concat_method   0.000000   0.000000   0.000000 (  0.000441)
append_method   0.000000   0.000000   0.000000 (  0.000787)
push_method     0.000000   0.000000   0.000000 (  0.000921)

...

N=100000

Rehearsal -------------------------------------------------
concat_method   0.210000   0.010000   0.220000 (  0.218780)
append_method   3.850000   0.000000   3.850000 (  3.850073)
push_method     5.070000   0.000000   5.070000 (  5.077609)
---------------------------------------- total: 9.140000sec

                    user     system      total        real
concat_method   0.160000   0.000000   0.160000 (  0.166845)
append_method   3.900000   0.030000   3.930000 (  3.941584)
push_method     5.020000   0.020000   5.040000 (  5.048860)
```


## descending_sort (**sort_reverse**)

Find out which sort in descending order is fastest
* sort_reverse_method       `values.sort.reverse`
* sort_reverse_each_method  `v= []; values.sort.reverse_each{|x| v << x }`
* sort_by_method            `values.sort_by{|x| -x }`
* sort_method               `values.sort{|x, y| y <=> x }`

Performance order

```
sort_reverse > sort_reverse_each >> sort_by >> sort
```

Proof

```
N=10

Rehearsal ------------------------------------------------------------
sort_reverse_method        0.000000   0.000000   0.000000 (  0.000918)
sort_reverse_each_method   0.000000   0.000000   0.000000 (  0.001664)
sort_by_method             0.000000   0.000000   0.000000 (  0.003129)
sort_method                0.000000   0.000000   0.000000 (  0.002197)
--------------------------------------------------- total: 0.000000sec

                               user     system      total        real
sort_reverse_method        0.000000   0.000000   0.000000 (  0.000816)
sort_reverse_each_method   0.000000   0.000000   0.000000 (  0.001226)
sort_by_method             0.000000   0.000000   0.000000 (  0.001545)
sort_method                0.000000   0.000000   0.000000 (  0.001327)

...

N=100000

Rehearsal ------------------------------------------------------------
sort_reverse_method       13.700000   0.000000  13.700000 ( 13.705529)
sort_reverse_each_method  17.300000   0.010000  17.310000 ( 17.327095)
sort_by_method            43.670000   0.010000  43.680000 ( 43.708177)
sort_method               79.240000   0.000000  79.240000 ( 79.283712)
------------------------------------------------- total: 153.930000sec

                               user     system      total        real
sort_reverse_method       13.760000   0.010000  13.770000 ( 13.775885)
sort_reverse_each_method  17.430000   0.010000  17.440000 ( 17.445740)
sort_by_method            44.600000   0.140000  44.740000 ( 44.761323)
sort_method               82.410000   0.010000  82.420000 ( 82.473854)
```


## dot_product (**while**/**numo_narray**)

Find out which dot-product method is fastest
* while_method           `while i < size sum += a[i] * b[i], ... `
* zip_method             `sum = 0; a.zip(b){|x, y| sum += x * y }`
* times_method           `sum = 0; a.size.times{|i| sum += a[i] * b[i] }`
* narray_method1         `NVector.to_na(a) * NVector.to_na(b)`
* narray_method2         `NVector[*a] * NVector[*b]`
* numo_narray_method     `Numo::NArray[*a].dot(Numo::NArray[*b])`
* inject_method          `(0...a.size).inject(0){|r, i| r + a[i] * b[i] }`
* vector_method          `Vector[*a].inner_product(Vector[*b])`
* zip_inject_method      `a.zip(b).inject(0){|sum, els| sum + els[0] * els[1] }`
* zip_map_inject_method  `a.zip(b).map{|x, y| x * y }.inject{|sum, el| sum + el }`
* matrix_method          `(Matrix.row_vector(a) * Matrix.column_vector(b)).element(0,0)`

Performance order

```
while > zip > times > inject > narray_1 > narray_2 >  vector > zip_inject > zip_map_inject > numo_narray > matrix
```

Proof
```
N=10

Rehearsal ---------------------------------------------------------
while_method            0.000000   0.000000   0.000000 (  0.000606)
zip_method              0.010000   0.000000   0.010000 (  0.000687)
times_method            0.000000   0.000000   0.000000 (  0.000712)
narray_method1          0.000000   0.000000   0.000000 (  0.002427)
narray_method2          0.000000   0.000000   0.000000 (  0.002595)
numo_narray_method      0.010000   0.000000   0.010000 (  0.008922)
inject_method           0.000000   0.000000   0.000000 (  0.001010)
vector_method           0.000000   0.000000   0.000000 (  0.002111)
zip_inject_method       0.000000   0.000000   0.000000 (  0.001445)
zip_map_inject_method   0.000000   0.000000   0.000000 (  0.002358)
matrix_method           0.010000   0.000000   0.010000 (  0.004533)
------------------------------------------------ total: 0.030000sec

                            user     system      total        real
while_method            0.000000   0.000000   0.000000 (  0.000582)
zip_method              0.000000   0.000000   0.000000 (  0.000665)
times_method            0.010000   0.000000   0.010000 (  0.000703)
narray_method1          0.000000   0.000000   0.000000 (  0.002811)
narray_method2          0.000000   0.000000   0.000000 (  0.002561)
numo_narray_method      0.010000   0.000000   0.010000 (  0.006959)
inject_method           0.000000   0.000000   0.000000 (  0.000990)
vector_method           0.010000   0.000000   0.010000 (  0.002062)
zip_inject_method       0.000000   0.000000   0.000000 (  0.001425)
zip_map_inject_method   0.000000   0.000000   0.000000 (  0.001880)
matrix_method           0.010000   0.000000   0.010000 (  0.003941)

...

N=100000

Rehearsal ---------------------------------------------------------
while_method            3.990000   0.000000   3.990000 (  3.994068)
zip_method              4.430000   0.000000   4.430000 (  4.430757)
times_method            5.280000   0.000000   5.280000 (  5.288968)
narray_method1          7.240000   0.010000   7.250000 (  7.243639)
narray_method2          7.580000   0.030000   7.610000 (  7.624018)
numo_narray_method     21.140000   0.070000  21.210000 ( 21.222851)
inject_method           6.560000   0.000000   6.560000 (  6.559955)
vector_method          11.100000   0.020000  11.120000 ( 11.124500)
zip_inject_method      13.420000   0.060000  13.480000 ( 13.494035)
zip_map_inject_method  17.330000   0.090000  17.420000 ( 17.428503)
matrix_method          23.770000   0.000000  23.770000 ( 23.783690)
---------------------------------------------- total: 122.120000sec

                            user     system      total        real
while_method            3.880000   0.000000   3.880000 (  3.874492)
zip_method              4.500000   0.000000   4.500000 (  4.504298)
times_method            5.250000   0.000000   5.250000 (  5.249917)
narray_method1          6.640000   0.010000   6.650000 (  6.645662)
narray_method2          7.060000   0.020000   7.080000 (  7.084665)
numo_narray_method     21.760000   0.100000  21.860000 ( 21.873323)
inject_method           7.010000   0.000000   7.010000 (  7.019779)
vector_method          11.220000   0.020000  11.240000 ( 11.257013)
zip_inject_method      14.190000   0.000000  14.190000 ( 14.194603)
zip_map_inject_method  17.110000   0.080000  17.190000 ( 17.206223)
matrix_method          23.910000   0.000000  23.910000 ( 23.925523)
```

Retry with only one Narray initialization

```
N=10

Rehearsal -----------------------------------------------------------------------------------
numo_narray_method with only one initialization   0.010000   0.000000   0.010000 (  0.002337)
narray_method1 with only one initialization       0.000000   0.000000   0.000000 (  0.000674)
narray_method2 with only one initialization       0.000000   0.000000   0.000000 (  0.000661)
-------------------------------------------------------------------------- total: 0.010000sec

                                                      user     system      total        real
numo_narray_method with only one initialization   0.000000   0.000000   0.000000 (  0.002054)
narray_method1 with only one initialization       0.000000   0.000000   0.000000 (  0.000612)
narray_method2 with only one initialization       0.000000   0.000000   0.000000 (  0.000611)

...

N=100000

Rehearsal -----------------------------------------------------------------------------------
numo_narray_method with only one initialization   0.090000   0.000000   0.090000 (  0.093345)
narray_method1 with only one initialization       0.210000   0.000000   0.210000 (  0.212762)
narray_method2 with only one initialization       0.220000   0.000000   0.220000 (  0.213266)
-------------------------------------------------------------------------- total: 0.520000sec

                                                      user     system      total        real
numo_narray_method with only one initialization   0.090000   0.000000   0.090000 (  0.093158)
narray_method1 with only one initialization       0.220000   0.000000   0.220000 (  0.212737)
narray_method2 with only one initialization       0.210000   0.000000   0.210000 (  0.213254)
```


## downcase (**unf**/**unicode**)

Find out which unicode downcase method is fastest
* unf_downcase_method            `s.to_nfd.downcase.to_nfc`
* unicode_downcase_method        `Unicode.downcase(s)`
* unicode_utils_downcase_method  `UnicodeUtils.downcase(s)`

Performance order

```
unf > unicode >> unicode_utils
```

Proof
```
N=10

Rehearsal -----------------------------------------------------------------
unf_downcase_method             0.000000   0.000000   0.000000 (  0.001107)
unicode_downcase_method         0.000000   0.000000   0.000000 (  0.000957)
unicode_utils_downcase_method   0.000000   0.000000   0.000000 (  0.002866)
-------------------------------------------------------- total: 0.000000sec

                                    user     system      total        real
unf_downcase_method             0.000000   0.000000   0.000000 (  0.001075)
unicode_downcase_method         0.000000   0.000000   0.000000 (  0.000926)
unicode_utils_downcase_method   0.000000   0.000000   0.000000 (  0.002854)

...

N=100000

Rehearsal -----------------------------------------------------------------
unf_downcase_method             6.990000   0.000000   6.990000 (  6.990581)
unicode_downcase_method         8.520000   0.000000   8.520000 (  8.533869)
unicode_utils_downcase_method  28.690000   0.000000  28.690000 ( 28.701476)
------------------------------------------------------- total: 44.200000sec

                                    user     system      total        real
unf_downcase_method             6.960000   0.010000   6.970000 (  6.972237)
unicode_downcase_method         8.970000   0.000000   8.970000 (  8.974831)
unicode_utils_downcase_method  29.880000   0.000000  29.880000 ( 29.901167)
```


## euclidean (**times**)

Find out which euclidean method is the fastest
* times_method       `a.size.times{|i| sum += (a[i] - b[i])**2 }`
* each_index_method  `a.each_with_index{|a_i, i| sum += (a_i - b[i])**2 }`
* zip_each_method    `a.zip(b).each{|a_i, b_i| sum += (a_i - b_i)**2 }`
* zip_inject_method  `a.zip(b).inject(0){|sum, v| sum + (v[0] - v[1])**2 }`
* zip_reduce_method  `a.zip(b).reduce(0){|sum, v| sum += (v[0]- v[1])**2 }`

Performance order

```
times > each > zip_each > zip_inject > zip_reduce
```

Proof
```
N=10

Rehearsal -----------------------------------------------------
times_method        0.000000   0.000000   0.000000 (  0.010299)
each_index_method   0.020000   0.000000   0.020000 (  0.012302)
zip_each_method     0.010000   0.000000   0.010000 (  0.015702)
zip_inject_method   0.020000   0.000000   0.020000 (  0.018636)
zip_reduce_method   0.020000   0.000000   0.020000 (  0.019035)
-------------------------------------------- total: 0.070000sec

                        user     system      total        real
times_method        0.010000   0.000000   0.010000 (  0.009656)
each_index_method   0.010000   0.000000   0.010000 (  0.011701)
zip_each_method     0.020000   0.000000   0.020000 (  0.015462)
zip_inject_method   0.020000   0.000000   0.020000 (  0.018524)
zip_reduce_method   0.020000   0.000000   0.020000 (  0.018682)

...

N=10000

Rehearsal -----------------------------------------------------
times_method        7.720000   0.000000   7.720000 (  7.726154)
each_index_method   9.050000   0.000000   9.050000 (  9.049181)
zip_each_method    13.810000   0.000000  13.810000 ( 13.816242)
zip_inject_method  15.530000   0.000000  15.530000 ( 15.544176)
zip_reduce_method  15.980000   0.000000  15.980000 ( 15.987543)
------------------------------------------- total: 62.090000sec

                        user     system      total        real
times_method        7.730000   0.000000   7.730000 (  7.737047)
each_index_method   9.060000   0.000000   9.060000 (  9.062186)
zip_each_method    12.740000   0.000000  12.740000 ( 12.745078)
zip_inject_method  15.460000   0.000000  15.460000 ( 15.470019)
zip_reduce_method  15.640000   0.000000  15.640000 ( 15.651138)
```


## hash_key_maxvalue (**key_max**)

Find out which method returning the key of maximum value is fastest
* key_max_method  `h.key(h.values.max)`
* each_if_method  `h.each{|k, v| if v > max ... }`
* max_by_method   `h.max_by{|k,v| v}[0]`


Performance order

```
key_max >~ each_if > max_by
```

Proof
```
N=10

Rehearsal --------------------------------------------------
key_max_method   0.000000   0.000000   0.000000 (  0.001011)
each_if_method   0.000000   0.000000   0.000000 (  0.000925)
max_by_method    0.000000   0.000000   0.000000 (  0.002019)
----------------------------------------- total: 0.000000sec

                     user     system      total        real
key_max_method   0.000000   0.000000   0.000000 (  0.000991)
each_if_method   0.000000   0.000000   0.000000 (  0.000890)
max_by_method    0.010000   0.000000   0.010000 (  0.001266)

...

N=10000

Rehearsal --------------------------------------------------
key_max_method   0.570000   0.000000   0.570000 (  0.572381)
each_if_method   0.750000   0.000000   0.750000 (  0.743081)
max_by_method    1.260000   0.000000   1.260000 (  1.268101)
----------------------------------------- total: 2.580000sec

                     user     system      total        real
key_max_method   0.570000   0.000000   0.570000 (  0.569910)
each_if_method   0.770000   0.010000   0.780000 (  0.783232)
max_by_method    1.270000   0.000000   1.270000 (  1.267043)
```


## init_hash_from_array (**each**)

Find out which hash init from array (val=0.0) method is the fastest
* each_method           `histo = {}; values.each{|x| histo[x] = 0.0 }`
* each_object_method    `values.each_with_object({}){|x, h| h[x] = 0.0 }`
* each_object_method2   `values.each_with_object(0.0).to_h`
* map_method            `values.map{|x| [x, 0.0] }.to_h`
* inject_method         `values.inject({}){|h, x| h[x] = 0; h }`
* inject_update_method  `values.inject({}){|h, x| h.update(x => 0.0) }`
* zip_method            `values.zip([0.0] * values.size).to_h`
* zip_method2           `values.zip(Array.new(values.size){0.0}).to_h`

Performance order

```
each >~ each_object >~ inject >~ map > ...
```

Proof
```
N=10

Rehearsal --------------------------------------------------------
each_method            0.000000   0.000000   0.000000 (  0.001458)
each_object_method     0.000000   0.000000   0.000000 (  0.001700)
each_object_method2    0.010000   0.000000   0.010000 (  0.003241)
map_method             0.000000   0.000000   0.000000 (  0.001671)
inject_method          0.000000   0.000000   0.000000 (  0.002480)
inject_update_method   0.000000   0.000000   0.000000 (  0.004130)
zip_method             0.010000   0.000000   0.010000 (  0.002720)
zip_method2            0.000000   0.000000   0.000000 (  0.002906)
----------------------------------------------- total: 0.020000sec

                           user     system      total        real
each_method            0.010000   0.000000   0.010000 (  0.001364)
each_object_method     0.000000   0.000000   0.000000 (  0.001597)
each_object_method2    0.000000   0.000000   0.000000 (  0.001734)
map_method             0.000000   0.000000   0.000000 (  0.001532)
inject_method          0.000000   0.000000   0.000000 (  0.001588)
inject_update_method   0.010000   0.000000   0.010000 (  0.003126)
zip_method             0.000000   0.000000   0.000000 (  0.001673)
zip_method2            0.010000   0.000000   0.010000 (  0.001964)

...

N=10000

Rehearsal --------------------------------------------------------
each_method            2.440000   0.000000   2.440000 (  2.442907)
each_object_method     2.450000   0.000000   2.450000 (  2.447144)
each_object_method2    2.350000   0.010000   2.360000 (  2.364303)
map_method             2.590000   0.000000   2.590000 (  2.594342)
inject_method          2.470000   0.000000   2.470000 (  2.471983)
inject_update_method   5.980000   0.060000   6.040000 (  6.031557)
zip_method             3.650000   0.000000   3.650000 (  3.660367)
zip_method2            2.620000   0.000000   2.620000 (  2.619267)
---------------------------------------------- total: 24.620000sec

                           user     system      total        real
each_method            2.310000   0.010000   2.320000 (  2.315545)
each_object_method     2.370000   0.000000   2.370000 (  2.374678)
each_object_method2    2.280000   0.000000   2.280000 (  2.280556)
map_method             2.340000   0.000000   2.340000 (  2.345105)
inject_method          2.570000   0.000000   2.570000 (  2.572273)
inject_update_method   6.430000   0.060000   6.490000 (  6.493361)
zip_method             3.330000   0.000000   3.330000 (  3.331762)
zip_method2            2.570000   0.000000   2.570000 (  2.579102)
```


## map_sum (**each**)

Find out which map & sum method is the fastest
* each_method        `v.each{|x| sum += Math.exp(x - max_value) }`
* inject_method      `v.inject(0){|sum, x| sum + Math.exp(x - max_value) }`
* map_inject_method  `v.map{|x| Math.exp(x - max_value) }.inject(0, :+)`
* map_reduce_method  `v.map{|x| Math.exp(x - max_value) }.reduce(0, :+)`


Performance order

```
each > inject > map_reduce >= map_inject
```

Proof
```
N=10

Rehearsal -----------------------------------------------------
each_method         0.000000   0.000000   0.000000 (  0.001398)
inject_method       0.000000   0.000000   0.000000 (  0.001141)
map_inject_method   0.010000   0.000000   0.010000 (  0.001453)
map_reduce_method   0.000000   0.000000   0.000000 (  0.001662)
-------------------------------------------- total: 0.010000sec

                        user     system      total        real
each_method         0.000000   0.000000   0.000000 (  0.000890)
inject_method       0.000000   0.000000   0.000000 (  0.001129)
map_inject_method   0.000000   0.000000   0.000000 (  0.001652)
map_reduce_method   0.000000   0.000000   0.000000 (  0.001459)

...

N=100000

Rehearsal -----------------------------------------------------
each_method         7.180000   0.000000   7.180000 (  7.182253)
inject_method       8.570000   0.000000   8.570000 (  8.582419)
map_inject_method  10.440000   0.000000  10.440000 ( 10.442393)
map_reduce_method  10.380000   0.000000  10.380000 ( 10.383667)
------------------------------------------- total: 36.570000sec

                        user     system      total        real
each_method         7.220000   0.000000   7.220000 (  7.226796)
inject_method       8.550000   0.000000   8.550000 (  8.548159)
map_inject_method  10.340000   0.000000  10.340000 ( 10.353201)
map_reduce_method  10.340000   0.010000  10.350000 ( 10.353450)
```


## max (**max**)

Find out which max method is the fastest
* max_method      `values.max`
* each_if_method  `values.each{|x| max = x if x > max }`
* sort_method     `values.sort[-1]`


Performance order

```
max >~ each_if >> sort
```

Proof
```
N=10

Rehearsal --------------------------------------------------
max_method       0.000000   0.000000   0.000000 (  0.000868)
each_if_method   0.000000   0.000000   0.000000 (  0.000540)
sort_method      0.000000   0.000000   0.000000 (  0.000499)
----------------------------------------- total: 0.000000sec

                     user     system      total        real
max_method       0.000000   0.000000   0.000000 (  0.000510)
each_if_method   0.000000   0.000000   0.000000 (  0.000489)
sort_method      0.000000   0.000000   0.000000 (  0.000473)

...

N=100000

Rehearsal --------------------------------------------------
max_method       3.220000   0.000000   3.220000 (  3.222982)
each_if_method   3.110000   0.000000   3.110000 (  3.115408)
sort_method      8.460000   0.000000   8.460000 (  8.466279)
---------------------------------------- total: 14.790000sec

                     user     system      total        real
max_method       3.120000   0.000000   3.120000 (  3.124356)
each_if_method   3.150000   0.000000   3.150000 (  3.148152)
sort_method      8.440000   0.010000   8.450000 (  8.458309)
```


## min_index (**index_min**)

Find out which index-min method is the fastest
* index_min_method       `v.index(v.min)`
* each_index_if_method   `v.each_with_index{|x, index| if x < min_val ... }`
* each_index_min_method  `v.each_with_index.min[-1]`


Performance order

```
index_min >~ each_index_if >> each_index_min
```

Proof

```
N=10

Rehearsal ---------------------------------------------------------
index_min_method        0.000000   0.000000   0.000000 (  0.000645)
each_index_if_method    0.000000   0.000000   0.000000 (  0.000756)
each_index_min_method   0.010000   0.000000   0.010000 (  0.002638)
------------------------------------------------ total: 0.010000sec

                            user     system      total        real
index_min_method        0.000000   0.000000   0.000000 (  0.000642)
each_index_if_method    0.000000   0.000000   0.000000 (  0.000753)
each_index_min_method   0.000000   0.000000   0.000000 (  0.002335)

...

N=100000

Rehearsal ---------------------------------------------------------
index_min_method        4.100000   0.000000   4.100000 (  4.098204)
each_index_if_method    4.850000   0.000000   4.850000 (  4.855688)
each_index_min_method  19.110000   0.000000  19.110000 ( 19.122968)
----------------------------------------------- total: 28.060000sec

                            user     system      total        real
index_min_method        4.110000   0.000000   4.110000 (  4.108489)
each_index_if_method    5.120000   0.000000   5.120000 (  5.117314)
each_index_min_method  18.950000   0.000000  18.950000 ( 18.958254)
```


## relu (**times_if**)

Find out which relu method is the fastest
* times_if_method         `values.size.times{|i| values[i] = 0 if values[i] < 0 }`
* map_conditional_method  `values.map{|x| x > 0 ? x : 0 }`
* map_max_method          `values.map{|x| [0, x].max }`


Performance order

```
times_if > map_contitional >> map_max
```

Proof
```
N=10

Rehearsal ----------------------------------------------------------
times_if_method          0.000000   0.000000   0.000000 (  0.000548)
map_conditional_method   0.000000   0.000000   0.000000 (  0.000663)
map_max_method           0.000000   0.000000   0.000000 (  0.003439)
------------------------------------------------- total: 0.000000sec

                             user     system      total        real
times_if_method          0.000000   0.000000   0.000000 (  0.000563)
map_conditional_method   0.000000   0.000000   0.000000 (  0.000695)
map_max_method           0.000000   0.000000   0.000000 (  0.002086)

...

N=100000

Rehearsal ----------------------------------------------------------
times_if_method          5.220000   0.000000   5.220000 (  5.212744)
map_conditional_method   5.750000   0.000000   5.750000 (  5.759523)
map_max_method          21.280000   0.020000  21.300000 ( 21.309097)
------------------------------------------------ total: 32.270000sec

                             user     system      total        real
times_if_method          5.220000   0.000000   5.220000 (  5.225656)
map_conditional_method   5.800000   0.000000   5.800000 (  5.803476)
map_max_method          21.160000   0.010000  21.170000 ( 21.181571)
```


## word_splits (**while**)

Find out which word-split method is the fastest
* while_method     `i = 0; while i <= val.size splits << ... end`
* times_method     `(val.size + 1).times{|i| splits << ... }`
* each_map_method  `(0..val.size).each.map{|i| [val[0...i], val[i..-1]] }`

Performance order

```
while > times > each_map
```

Proof
```
Word=interrogation

Rehearsal ---------------------------------------------------
while_method      0.530000   0.000000   0.530000 (  0.532453)
times_method      0.550000   0.000000   0.550000 (  0.547459)
each_map_method   0.590000   0.000000   0.590000 (  0.590646)
------------------------------------------ total: 1.670000sec

                      user     system      total        real
while_method      0.530000   0.000000   0.530000 (  0.531662)
times_method      0.550000   0.000000   0.550000 (  0.547198)
each_map_method   0.590000   0.000000   0.590000 (  0.590871)
```
