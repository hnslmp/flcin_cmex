%Settling Time Threshold
st_threshold = 0.02
output1 = out.get('out1');
out1_step = stepinfo(output1,'SettlingTimeThreshold',st_threshold)

output2 = out.get('out2');
out2_step = stepinfo(output2,'SettlingTimeThreshold',st_threshold)

konstanta = [1.47343217607515e-05]