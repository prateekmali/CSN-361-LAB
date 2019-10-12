set ns [new Simulator]

set nf [open Q1.nam w]
$ns namtrace-all $nf

set tf [open Q1.tr w]
$ns trace-all $tf

proc finish { } {
    global ns nf tf
    $ns flush-trace
    close $nf
    close $tf
    exec nam Q1.nam &
    exec awk -f Q1.awk Q1.tr &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 350000b 2ms DropTail
$ns duplex-link $n1 $n2 55000b 1ms DropTail
$ns queue-limit $n0 $n1 10
$ns queue-limit $n2 $n1 5

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0
$ns connect $udp0 $null0

$ns at 0.1 "$cbr0 start"
$ns at 1.0 "finish"

$ns run