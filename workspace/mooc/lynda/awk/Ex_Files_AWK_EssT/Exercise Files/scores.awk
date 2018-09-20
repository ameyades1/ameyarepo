BEGIN {
FS="\t";
  print "<table>";
  print "<tr>";
  print "<th><b>Bowler</b></th>";
  for(i = 1; i <= 7; i++)
  {
    print "<th>Round" i "</th>";
  }
  print "</tr>";
}

{
  print "<tr>";
  print "\t<td><b>" $1 "</b></td>";
  for(i = 2; i <= 8; i++)
  {
    print "\t<td>" $i "</td>";
    total[i] += $i;
  }
  print "</tr>";
}

END {

  print "<tr>";
  print "<td><i><b><u>Average</u></b></i></th>";
  for(i = 2; i <= 8; i++)
  {
    print "<td>" int(total[i]/NR) "</td>";
  }
  print "</tr>";
  print "</table>";
}
