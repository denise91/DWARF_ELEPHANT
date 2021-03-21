function  x_new = apply_geom_trafo(subdomain_id,x_old,r0,l0)
L = 0.1;
r = 3e-3;
l = 4e-2;
r_0 = r0;
l_0 = l0;
d = (8.0/3.0)*r;
h = (4.0/3.0)*l;

if (subdomain_id==1)
    matrix = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==2)
    matrix = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [-(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==3)
    matrix = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [-(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==4)
    matrix = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==5)
    matrix = [(r + r_0)/(2*r) (r - r_0)/(2*r) 0; (r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [0; 0; -(L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==6)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==7)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==8)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==9)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==10)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) -(d*(r - r_0))/(r*(d + h)); 0 -(h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
end 

if (subdomain_id==11)
    matrix = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==12)
    matrix = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==13)
    matrix = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==14)
    matrix = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==15)
    matrix = [(d*r_0 + h*r)/(r*(d + h)) 0 (d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; (h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
    vec = [0; -(L*d*(r - r_0))/(2*r*(L - d)); 0];
end 

if (subdomain_id==16)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==17)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==18)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==19)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==20)
    matrix = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) (d*(r - r_0))/(r*(d + h)); 0 (h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
end 

if (subdomain_id==21)
    matrix = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==22)
    matrix = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==23)
    matrix = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
    vec = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==24)
    matrix = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
    vec = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
end 

if (subdomain_id==25)
    matrix = [(d*r_0 + h*r)/(r*(d + h)) 0 -(d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; -(h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
    vec = [0; (L*d*(r - r_0))/(2*r*(L - d)); 0];
end 

if (subdomain_id==26)
    matrix = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==27)
    matrix = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [-(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==28)
    matrix = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==29)
    matrix = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [-(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==30)
    matrix = [(r + r_0)/(2*r) -(r - r_0)/(2*r) 0; -(r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
    vec = [0; 0; (L*h*(l - l_0))/(2*l*(L - h))];
end 

if (subdomain_id==31)
    matrix = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
    vec = [0; 0; 0];
end 

if (subdomain_id==32)
    matrix = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
    vec = [0; 0; 0];
end 

x_new = matrix*x_old + vec;
end 
