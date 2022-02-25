for((;;))
do
	leaks minishell | grep -A10 for
	sleep 3
	clear
done
