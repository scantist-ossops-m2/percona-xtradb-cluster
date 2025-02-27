--echo Killing server ...

if (!$kill_signal)
{
--let $kill_signal = 9
}

# Write file to make mysql-test-run.pl expect the crash, but don't start it
--let $_server_id= `SELECT @@server_id`
--let $_expect_file_name= $MYSQLTEST_VARDIR/tmp/mysqld.$_server_id.expect
--exec echo "wait" > $_expect_file_name

# Kill the connected server
--disable_reconnect
--let KILL_SIGNAL_VALUE = $kill_signal
--let KILL_NODE_PIDFILE = `SELECT @@pid_file`

--perl
        my $kill_sig = $ENV{'KILL_SIGNAL_VALUE'};
        my $pid_filename = $ENV{'KILL_NODE_PIDFILE'};
        my $mysqld_pid = `cat $pid_filename`;
        chomp($mysqld_pid);
        system("kill -s $kill_sig $mysqld_pid  ||:");
        exit(0);
EOF

--source include/wait_until_disconnected.inc
