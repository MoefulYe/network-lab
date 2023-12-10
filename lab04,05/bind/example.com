$TTL 900
@ IN SOA example.com. postmaster.example.com. (
        2020062101      ; Serial Number
        1800            ; Refresh
        900             ; Retry
        1209600         ; expire
        900             ; minimum
        )
;
      IN    NS  example.com.
      IN    A   1.2.3.4
www   IN    A   172.17.0.2
