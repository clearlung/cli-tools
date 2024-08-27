date=$(date +"%m/%d %H:%M") 
dir="/home/programming/cli-tools"

git add $dir
git commit -m "$date" 
git push -u origin main
