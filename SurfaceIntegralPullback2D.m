clear all
clc

syms g11
syms g12
syms g21
syms g22

syms del_x_xi1
syms del_x_xi2
syms del_y_xi1
syms del_y_xi2

syms ii
syms jj

syms x_dash
syms y_dash

G = [g11 g12; g21 g22];
%del_r_xi1 = [del_x_xi1; del_y_xi1];
%del_r_xi2 = [del_x_xi2; del_y_xi2];

%det([(G*del_r_xi1).';(G*del_r_xi2).'])

R_dash = [x_dash; y_dash];

collect(norm(G*R_dash),[x_dash; y_dash])
