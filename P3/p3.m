ts = [0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3 3.1 3.2 3.3 3.4 3.5 3.6 3.7 3.8 3.9 4 4.1 4.2 4.3 4.4 4.5 4.6 4.7 4.8 4.9 5 5.1 5.2 5.3 5.4 5.5 5.6 5.7 5.8 5.9 6 6.1 6.2 6.3 6.4 6.5 6.6 6.7 6.8 6.9 7 7.1 7.2 7.3 7.4 7.5 7.6 7.7 7.8 7.9 8 8.1 8.2 8.3 8.4 8.5 8.6 8.7 8.8 8.9 9 9.1 9.2 9.3 9.4 9.5 9.6 9.7 9.8 9.9 10 10.1 10.2 10.3 10.4 10.5 10.6 10.7 10.8 10.9 11 11.1 11.2 11.3 11.4 11.5 11.6 11.7 11.8 11.9 12 12.1 12.2 12.3 12.4 12.5 12.6 12.7 12.8 12.9 13 13.1 13.2 13.3 13.4 13.5 13.6 13.7 13.8 13.9 14 14.1 14.2 14.3 14.4 14.5 14.6 14.7 14.8 14.9 15 15.1 15.2 15.3 15.4 15.5 15.6 15.7 15.8 15.9 16 16.1 16.2 16.3 16.4 16.5 16.6 16.7 16.8 16.9 17 17.1 17.2 17.3 17.4 17.5 17.6 17.7 17.8 17.9 18 18.1 18.2 18.3 18.4 18.5 18.6 18.7 18.8 18.9 19 19.1 19.2 19.3 19.4 19.5 19.6 19.7 19.8 19.9 20];
ys = [0.0 7.71173e-17 7.27609e-13 1.11175e-10 3.47125e-09 4.62728e-08 3.59235e-07 1.91191e-06 7.70971e-06 2.51062e-05 6.90295e-05 0.000165504 0.000354644 0.000692393 0.00125095 0.00211821 0.00339673 0.00520249 0.00766338 0.010917 0.0151079 0.0203845 0.0268957 0.0347874 0.0441997 0.0552621 0.068089 0.082774 0.099385 0.117959 0.1385 0.16097 0.185294 0.211349 0.238972 0.267949 0.298028 0.328914 0.360276 0.391754 0.422956 0.453475 0.482887 0.510764 0.536679 0.560215 0.580969 0.598562 0.612643 0.622894 0.629043 0.630857 0.628157 0.62081 0.608742 0.59193 0.570411 0.544275 0.513669 0.478795 0.439904 0.397294 0.351314 0.302349 0.250825 0.197198 0.141954 0.0855958 0.0286474 -0.0283583 -0.0848827 -0.140388 -0.194345 -0.246235 -0.295558 -0.341837 -0.384623 -0.423499 -0.458088 -0.488053 -0.513102 -0.532991 -0.547526 -0.556566 -0.560026 -0.557872 -0.550132 -0.536883 -0.51826 -0.494451 -0.465695 -0.432279 -0.394541 -0.352856 -0.307643 -0.259354 -0.208471 -0.155502 -0.100979 -0.0454456 0.0105422 0.0664255 0.121646 0.175652 0.227904 0.277878 0.325076 0.369026 0.409289 0.445463 0.477187 0.504142 0.52606 0.542722 0.553961 0.559666 0.559779 0.554298 0.543279 0.526832 0.50512 0.478362 0.446825 0.410823 0.370716 0.326905 0.279827 0.229953 0.177783 0.123836 0.0686515 0.0127806 -0.0432182 -0.0987848 -0.153364 -0.206411 -0.257395 -0.305808 -0.351166 -0.393015 -0.430936 -0.464552 -0.493526 -0.517569 -0.536441 -0.549953 -0.55797 -0.560412 -0.557254 -0.548528 -0.534322 -0.514778 -0.490089 -0.460504 -0.426317 -0.38787 -0.345549 -0.299775 -0.251006 -0.199729 -0.146455 -0.0917183 -0.0360656 0.0199471 0.0757605 0.130817 0.184568 0.236474 0.286017 0.332701 0.376062 0.415665 0.451116 0.482059 0.508185 0.529233 0.544994 0.555309 0.560076 0.559247 0.55283 0.540889 0.523544 0.500967 0.473385 0.441074 0.404356 0.363597 0.319205 0.271623 0.221328 0.168821 0.114628 0.0592898 0.00335824 -0.052607 -0.108046 -0.162405 -0.215142 -0.265729 -0.313661];
hold on;
plot (ts, ys);
plot (ts, sin(ts) + sin(10*ts))
hold off;
ys(-1)