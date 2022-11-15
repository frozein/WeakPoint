all:
	cd build; cmake ..; make; cd ..; cd assets; ../build/scarletgamejam; cd ../

git:
	git add .
	git commit -m "$m"
	git push -u origin master