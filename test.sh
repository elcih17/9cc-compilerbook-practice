#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./9cc "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
      echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 "0;"
assert 42 "42;"
assert 21 "5+20-4;"
assert 41 " 12 + 34 - 5 ;"
assert 6 "2*3;"
assert 3 "6/2;"
assert 9 "3*(2+1);"
assert 1 "-10+11;"
assert 10 "- -10;"

assert 1 "1 == 1;"
assert 0 "1 == 0;"
assert 1 "1 != 0;"
assert 0 "1 != 1;"

assert 1 "0 < 1;"
assert 0 "1 < 1;"
assert 0 "2 < 1;"

assert 1 "0 <= 1;"
assert 1 "1 <= 1;"
assert 0 "2 <= 1;"

assert 1 "1 > 0;"
assert 0 "1 > 1;"
assert 0 "1 > 2;"

assert 1 "1 >= 0;"
assert 1 "1 >= 1;"
assert 0 "1 >= 2;"

assert 1 "a=1; a;"
assert 2 "a=1; a+1;"
assert 4 "a=b=2; a+b;"
assert 6 "foo=1; bar=2+3; foo+bar;"

assert 5 "return 5; return 6;"
assert 14 "a=3; b=5*6-8; return a+b/2;"

echo OK
