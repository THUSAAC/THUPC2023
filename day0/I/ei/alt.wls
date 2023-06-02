#!/usr/bin/env wolframscript
(* ::Package:: *)

n = 2;

m = 2;

SeriesCoefficient[(((1 - X * Y) ^ 2 - X^2) / ((1 + X * Y) ^ 2 - X^2))
     ^ (1 / 4) * Exp[(n + m) * X + n * Y], {X, 0, n}, {Y, 0, m}] * Factorial[
    n] * Factorial[m]
