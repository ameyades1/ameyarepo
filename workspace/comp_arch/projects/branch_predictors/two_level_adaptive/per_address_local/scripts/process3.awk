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

#printf("Trace = %-11s  Accuracy = %.3f\n", trace, $3);

accuracy_arr[rat_sz,ghr_sz,ahrt_sz,ahrt_ass,btb_sz,trace]=$3;
}

END {
  printf("Branch Predictor Simulation Results\n\n");
  printf("Detected Configurations\n");
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
  
  printf("\n\n");
  n=asorti(accuracy_arr, sorted);
  
#  printf("\n--SUMMARY--\n");
#  printf("Trace       RAT    GHR_SZ  AHRT_SZ  AHRT_ASS  BTB_SZ  Accuracy\n");
#  printf("--------------------------------------------------------------\n");
#  for(i=1 ;i<int(n/5); i++){

#    printf("%-11s %-5d  %-5d   %-5d    %-5d     %-5d   %.3f\n", config[6], config[1], config[2], config[3], config[4], config[5], accuracy_arr[sorted[i]]);


    printf("Trace       RAT    GHR_SZ  AHRT_SZ  AHRT_ASS  BTB_SZ  Accuracy\n");
    printf("--------------------------------------------------------------\n");
  for(i=1; i<=n;i++) {
    split(sorted[i], config, SUBSEP);
    printf("%-11s %-5d  %-5d   %-5d    %-5d     %-5d   %.3f\n", config[6], config[1], config[2], config[3], config[4], config[5], accuracy_arr[sorted[i]]);
  }

}

