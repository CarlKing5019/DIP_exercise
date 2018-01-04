%�õ��������͸�˹����c���룬����ֱ��д��h�ļ�������д��txt�ٸ��ƹ�ȥ�ˣ���Ҫ��Ҫ�м�Ķ��š�
fid=fopen('cos.txt','wt');
fid_g=fopen('gaus.txt','wt');

cos_window = hann(64) * hann(64)';
cos_window=cos_window(:);
fprintf(fid,'float cos_window_64_64[4096]={');
fprintf(fid_g,'float gaus_window_64_64[4096]={');

%��������Ǹ�˹��������������������
target_sz=[32,32];
sz=[64,64];
output_sigma_factor=1/16;
output_sigma = sqrt(prod(target_sz)) * output_sigma_factor;    %����������������Ǹ�aqrt��mn��/16.
[rs, cs] = ndgrid((1:sz(1)) - floor(sz(1)/2), (1:sz(2)) - floor(sz(2)/2));
%����ʵ������ȥ�������꣬x��y����meshһ��rs��cs�Ͷ���
y = exp(-0.5 / output_sigma^2 * (rs.^2 + cs.^2));  %��˹�����������������
y=y(:);

for i=1:size(cos_window)
    fprintf(fid,'%f,',cos_window(i));
    fprintf(fid_g,'%f,',y(i));
end
fclose(fid);
fclose(fid_g);

