#/bin/awk -f
BEGIN { FS = "," }
{
if (NR == 1)
{
        saldo [NR] = $6;
}
        else
        {
                saldoPoOperacji = saldo[NR-1] + $4;
                if(saldoPoOperacji != $6)
                {
                        print "BLAD PLATNOSCI : LINIA ",
                         NR," Saldo po operacji: ",
                         saldoPoOperacji,
                        "Saldo ksiegowe: ", $6;
                }
        saldo[NR] = $6
        }
}
END{};

#uruchomiono,sprawdzono,przetestowano serwer diablo