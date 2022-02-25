for((;;))
do
	leaks minishell | grep -A10 for
	sleep 1
	clear
done
