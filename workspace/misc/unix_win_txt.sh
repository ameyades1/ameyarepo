awk '{sub("$", "\r"); print }' $1 > $2
