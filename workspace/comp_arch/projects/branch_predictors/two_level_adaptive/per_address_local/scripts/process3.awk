/^RAT/ {rat_size[$3]=$3}
/^GHR/ {ghr_size[$3]=$3}
/^AHRT Size/ {ahrt_size[$3]=$3}
/^AHRT Asso/ {ahrt_asso[$3]=$3}
/^BTB Size/ {btb_size[$3]=$3}

END {
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
}

