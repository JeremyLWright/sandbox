function float_diff = float_dist(floats)
float_size = size(floats);
float_shift = floats(2:float_size(2));
float_shift = [[float_shift] [0]];
float_diff =  float_shift - floats;
//plot(floats, float_diff, "o")
endfunction
