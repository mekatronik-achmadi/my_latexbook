# How to Contribute (using Git and Github)

This general guide explain about how to contribute using Git SCM and repository hosted by Github.

**Note:** This guide only for pull-request and merge method without any Collaborator access provided by Github .

## Why Git?

One of the most popular version control systems for software is Git. Git was created in 2005 by Linus Torvalds, the creator of the Linux kernel.

Many projects maintain their files in a Git repository, and sites like GitHub, GitLab, and Bitbucket have made sharing and contributing to code simple, valuable, and effective. Every working directory in Git is a full-fledged repository with complete history and tracking independent of network access or a central server.

Git is so useful for open-source projects because it facilitates the contributions of many developers. Each contributor can branch off from the main or master branch of the code base repository to isolate their own changes, and can then make a pull request to have these changes integrated into the main project.

More reading about **Git**, see [here](https://www.digitalocean.com/community/tutorials/contributing-to-open-source-getting-started-with-git)

----

## Requirement:

This minimun requirement to working in collaborative sense.

  * Github Account
  * Git client (Linux/BSD/Windows/Mac), prefreably featured :
    * Git Bash or simply Bash shell
    * Git GUI or Git Cola

----

## General steps:

Here some general step how to do collaborative work using Git and Github.

----

### Step to need do only once

  * Fork this example [project repository](https://github.com/mekatronik-achmadi/photsim) to your Github account.
![fork](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/fork.png)

  * Clone your fork to your computer as **master** branch (for example your github username is **friend**). Command on terminal:
~~~
git clone  https://github.com/friend/photsim.git
~~~
  * Enter to project clone directory. Command on terminal:
~~~
cd ./photsim
git checkout master
~~~
  * Add this repository as **upstream** and check it. Command on terminal:
~~~
git remote add upstream https://github.com/mekatronik-achmadi/photsim.git
git remote -v
~~~

----

### Step to need do as workflow

  * Sync your **master** clone to the **upstream**. Command on terminal:
~~~
cd ./photsim
git fetch upstream
git checkout master
git merge upstream/master
git push origin master
~~~
  * Create your own branch (for example **mybranch**). Command on terminal:
~~~
git branch mybranch
git show-branch -a
git checkout mybranch
~~~
  * Do whatever your work on this branch.
  * Stage and commit your all work.  Command on terminal:
~~~
git add -A
git commit -m "my work today"
~~~
  * Push your work on **mybranch** to your fork on Github. Command on terminal:
~~~
git push -u origin mybranch
~~~
  * From your fork on Github, select branch (**mybranch**) to pull request.
![selbranch](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/selbranch.png) ![pullreq](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/pullreq.png)

  * Review your patch on your work.
![patchreview](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/patchreview.png)

  * Then create pull request.
![conpullreq](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/conpullreq.png)

  * If your work accepted, your pull request will succesfully merged to **upstream**.
![mergeok](https://raw.githubusercontent.com/mekatronik-achmadi/my_latexbook/master/Git/images/png/mergeok.png)

  * After pull request succesfully merged, you can delete **mybranch**. Command on terminal:
~~~
git checkout master
git branch -d mybranch
git show-branch -a
git push origin --delete mybranch
~~~

----

### Step to merging pull request
**Note:** This only do by project maintainer. If you are not the project maintainer, you may skip reading this step.

  * Pull temporary branch from pull request. (for example from **friends** and branch **mybranch**). Command on terminal:
~~~
git checkout master
git branch friends-mybranch
git checkout friends-mybranch
git pull https://github.com/friends/photsim.git mybranch
~~~
  * Do test on this branch and make sure everything run as designed.
  * Merge pull request. Command on terminal:
~~~
git checkout master
git merge -m "his work" friends-mybranch
git push origin master
~~~
  * Delete temporary branch. Command on terminal:
~~~
git branch -d friends-mybranch
git show-branch -a
~~~

----

More detailed about **how to work in pull request workflow**, see [here](https://www.digitalocean.com/community/tutorials/how-to-create-a-pull-request-on-github)

or detailed about **Rebase and Update Pull Request**, see [here](https://www.digitalocean.com/community/tutorials/how-to-rebase-and-update-a-pull-request)

Futher reading about **introduction to open source collaborative workflow**, see [here](https://www.digitalocean.com/community/tutorial_series/an-introduction-to-open-source)

And another good reading about basic Git workflow, see [here](https://nathanj.github.io/gitguide/), or [here](https://nathanj.github.io/gitguide/tour.html)
