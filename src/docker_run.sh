make uninstall
docker image rm -f bodgerun/tetris
docker image build -t bodgerun/tetris -f Dockerfile ..
docker container run -it --rm bodgerun/tetris
