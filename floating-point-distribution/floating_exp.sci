exec("float_dist.sci");
exec("read_files.sci");
result = read_files();

x = result(1,:);
y = result(2,:);
z = result(3,:);
z_shift = z/1D-40;

zd = float_dist(z_shift);
subplot(1,3,1);
xtitle("","" ,"1E-40");
plot(zd(1:10));

subplot(1,3,2);
xtitle("","" ,"1E-40");
plot(zd(1:100));

subplot(1,3,3);
xtitle("","" ,"1E-40");
plot(zd(1:1000));

