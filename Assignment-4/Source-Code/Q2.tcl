set netSimInstance [new Simulator]
 
set namFile [open Q2.nam w]
$netSimInstance namtrace-all $namFile

set traceFile [open Q2.tr w]
$netSimInstance trace-all $traceFile

proc finish {}   {
    global netSimInstance traceFile namFile
    $netSimInstance flush-trace
    close $traceFile
    close $namFile
    exec nam Q2.nam &
    exec awk -f Q2.awk Q2.tr &
    exit 0
}

set node0 [$netSimInstance node]
set node1 [$netSimInstance node]
set node2 [$netSimInstance node]
set node3 [$netSimInstance node]
set node4 [$netSimInstance node]
set node5 [$netSimInstance node]

$netSimInstance duplex-link $node0 $node2 .1Mb 10ms DropTail
$netSimInstance duplex-link $node2 $node1 .1Mb 10ms DropTail
$netSimInstance duplex-link $node2 $node3 .1Mb 10ms DropTail
$netSimInstance duplex-link $node3 $node4 .1Mb 10ms DropTail
$netSimInstance duplex-link $node3 $node5 .1Mb 10ms DropTail

Agent/Ping instproc recv {from rtt} {
        $self instvar node_
        puts "node [$node_ id] received ping answer from \
              $from with round-trip-time $rtt ms."
}

set pingAgent0 [new Agent/Ping]
set pingAgent1 [new Agent/Ping]
set pingAgent2 [new Agent/Ping]
set pingAgent3 [new Agent/Ping]
set pingAgent4 [new Agent/Ping]
set pingAgent5 [new Agent/Ping]


$netSimInstance attach-agent $node0 $pingAgent0
$netSimInstance attach-agent $node1 $pingAgent1
$netSimInstance attach-agent $node2 $pingAgent2
$netSimInstance attach-agent $node3 $pingAgent3
$netSimInstance attach-agent $node4 $pingAgent4
$netSimInstance attach-agent $node5 $pingAgent5


$netSimInstance queue-limit $node0 $node2 2
$netSimInstance queue-limit $node2 $node1 2
$netSimInstance queue-limit $node2 $node3 2
$netSimInstance queue-limit $node3 $node4 1
$netSimInstance queue-limit $node3 $node5 1

$netSimInstance connect $pingAgent0 $pingAgent4
$netSimInstance connect $pingAgent5 $pingAgent1

$netSimInstance at 0.15 "$pingAgent0 send"
$netSimInstance at 0.1 "$pingAgent5 send"
$netSimInstance at 2.0 "finish"

 $netSimInstance run