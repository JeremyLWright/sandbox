function result = read_files()

float_dist_x = [];
float_dist_y = [];
float_dist_z = [];

fidx = mopen("float_dist_x.dat", "r");
fidy = mopen("float_dist_y.dat", "r");
fidz = mopen("float_dist_z.dat", "r");

num_read = 1
while(num_read == 1)
	[num_read, temp] = mfscanf(fidx, "%f");
	float_dist_x = [[float_dist_x] [temp]];
end


num_read = 1
while(num_read == 1)
	[num_read, temp] = mfscanf(fidy, "%f");
	float_dist_y = [[float_dist_y] [temp]];
end

num_read = 1
while(num_read == 1)
	[num_read, temp] = mfscanf(fidz, "%f");
	float_dist_z = [[float_dist_z] [temp]];
end
result = [[float_dist_x]; [float_dist_y]; [float_dist_z]];

mclose(fidx);
mclose(fidy);
mclose(fidz);
endfunction
