/^DIST/ {
trace=$1;
getline;
getline; rat_sz=$3;   rat_size[$3]=$3;
getline; ghr_sz=$3;   ghr_size[$3]=$3;
getline; ahrt_sz=$3;  ahrt_size[$3]=$3;
getline; ahrt_ass=$3; ahrt_asso[$3]=$3;
getline; btb_sz=$3;   btb_size[$3]=$3;

do {
  getline;
}while($2 != "accuracy:");

accuracy_arr[rat_sz,ghr_sz,ahrt_sz,ahrt_ass,btb_sz,trace] = $3;
}

END {
  printf("Branch Predictor Simulation Results\n\n");
  printf("Detected Configurations:\n");
  printf("------------------------\n");
  printf("RAT Sizes = \t")
  for(i in rat_size) {printf("%d ", rat_size[i]);}
  printf("\nGHR Sizes = \t")
  for(i in ghr_size) {printf("%d ", ghr_size[i]);}
  printf("\nAHRT Sizes = \t")
  for(i in ahrt_size) {printf("%d ", ahrt_size[i]);}
  printf("\nAHRT Asso = \t")
  for(i in ahrt_asso) {printf("%d ", ahrt_asso[i]);}
  printf("\nBTB Sizes = \t")
  for(i in btb_size) {printf("%d ", btb_size[i]);}
  
  num_config = length(rat_size) * length(ghr_size) * length(ahrt_size) * length(ahrt_asso) * length(btb_size);
  printf("\n\nTotal Configurations = %d\n\n", num_config); 
  
  printf("\nSummary of Results: \n");
  printf("--------------------------------------------------------------------------------\n");
  printf("        Configuration                  |           Trace Accuracy               \n\n");
  printf("RAT  GHR_SZ  AHRT_SZ  AHRT_ASS  BTB_SZ | FP      INT     MM      SERV   | Avg   \n");
  printf("--------------------------------------------------------------------------------\n");

  n=asorti(accuracy_arr, sorted);

  for(k = 1; k <= num_config; k++) { #Num configurations
    avg_acc = 0;
    for(z = 1; z <= 4; z++) { acc[z] = 0; }
    
    for(j = 1; j <= 4; j++) {  #Four trace types 
      for(i = 1; i <= 5; i++) {  #Five traces per type
        split(sorted[(k-1)*20 + (j-1)*5 + i], config, SUBSEP);
        acc[j] += accuracy_arr[sorted[(k-1)*20 + (j-1)*5 + i]];
        }
        avg_acc += acc[j]/5;
      }
      printf("%-4d %-5d   %-5d    %-5d     %-5d  | %.3f  %.3f  %.3f  %.3f | %.3f\n", 
		config[1], config[2], config[3], config[4], config[5], acc[1]/5, 
		acc[2]/5, acc[3]/5, acc[4]/5, avg_acc/4);
   }
   
   printf("\n\n");
   printf("Detailed Results:\n");

    printf("Trace       RAT    GHR_SZ  AHRT_SZ  AHRT_ASS  BTB_SZ  Accuracy\n");
    printf("--------------------------------------------------------------\n");
  for(i=1; i<=n;i++) {
    split(sorted[i], config, SUBSEP);
    printf("%-11s %-5d  %-5d   %-5d    %-5d     %-5d   %.3f\n", config[6], config[1], config[2], config[3], config[4], config[5], accuracy_arr[sorted[i]]);
  }
}

