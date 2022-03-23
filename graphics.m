t1 = dlmread("results_M.csv");
t2 = dlmread("results_N.csv");
t3 = dlmread("results_K.csv");
t4 = dlmread("results_M_1.csv");
t5 = dlmread("results_N_1.csv");
t6 = dlmread("results_K_1.csv");


#subplot(1,3,1);
figure;
plot(t1(:,1), t1(:,2));
hold on;
plot(t4(:,1), t4(:,2));
grid on; grid minor on;
#axis("square");
axis([0 8192 0 25]);
xlabel('Q','fontsize',18);
ylabel('P','fontsize',18);


#subplot(1,3,2);
figure;
plot(t2(:,1), t2(:,2));
hold on;
plot(t5(:,1), t5(:,2));
grid on; grid minor on;
#axis("square");
axis([0 8192 0 25]);
xlabel('L','fontsize',18);
ylabel('P','fontsize',18);

#subplot(1,3,3);
figure;
plot(t3(:,1), t3(:,2));
hold on;
plot(t6(:,1), t6(:,2));
grid on; grid minor on;
#axis("square");
axis([0 8192 0 25]);
xlabel('F','fontsize',18);
ylabel('P','fontsize',18);