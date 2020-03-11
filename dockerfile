# sudo docker build -t monimage dockerfile
# sudo docker run -it monimage
FROM gcc:8.2.0
RUN git clone https://github.com/faroke/jjSH.git && cd jjSH && gcc main.c
CMD cd jjSH && git pull && /bin/bash
