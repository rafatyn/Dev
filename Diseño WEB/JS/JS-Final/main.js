var canvas = document.getElementById('canvas');
var context = canvas.getContext('2d');
var fps = 0, actualFps = 0, deadStop = false;
var scale = 0.65, scalePlayer = 0.75;
var aliensItems = [], obstaclesItems = [], aliensBullets = [], bulletsItem = [], frontAliens = [0, 1, 2, 3, 4, 5, 6, 7];
var space;
var player;
var keyMap = {};
var intervals = [];
init();

function init() {
    fps = 0; actualFps = 0;
    var image = new Image();
    image.src = "spaceInvaders.gif";
    image.addEventListener("load", function() {
        loadAliens(image);
        loadPlayer(image);
        loadObstacles(image)
    });
    space = new Image();
    space.src = "bg.jpg";
    space.addEventListener("load", start);
}

function start() {
    intervals.push(setInterval(render, 1000/144));
    intervals.push(setInterval(aliensMove, 600));
    intervals.push(setTimeout(aliensShoot, 2000+(Math.random()*3000)));
    intervals.push(setInterval(bulletsMove, 1000/60));
    intervals.push(setInterval(function() { actualFps = fps; fps = 0; }, 1000));
}

function render() {
    clear();
    fps++;
    aliensItems.forEach(function(e) {
        e.render();
    });
    if(player != undefined) { player.render(); }
    bulletsItem.forEach(function(e) {
        e.render();
    });
    aliensBullets.forEach(function(e) {
        e.render();
    });
    obstaclesItems.forEach(function(e) {
        e.render();
    });
    renderHud();
}

function clear() {
    context.clearRect(0,0,canvas.width, canvas.height);
    context.drawImage(space, 0, 0, space.width, space.height, 0, 0, canvas.width, canvas.height);
}

function bulletsMove() {
    if(!deadStop) {
        bulletsItem.forEach(function(e) {
            e.move();
        });
        aliensBullets.forEach(function(e) {
            e.move();
        });
    }
}

function aliensMove() {
    if(!deadStop) {
        aliensItems.forEach(function(e) {
            e.move();
        });
    }
}

function aliensShoot() {
    if(!deadStop) {
        var numero = Math.random();
        for(var i=1; i<9; i++) {
            if(numero<(i/8)) {
                numero = frontAliens[i-1];
                break;
            }
        }
        if(numero != -1) {
            aliensBullets.push({source: player.source,
                                posc: {x: 487, y: 394},
                                sizes: {x: 28, y: 51},
                                sizef: {x: 28*scale, y: 51*scale},
                                posscreen: {x: aliensItems[numero].posscreen.x + (aliensItems[numero].sizef.x / 2) - (28*scale/2), y: aliensItems[numero].posscreen.y + aliensItems[numero].sizef.y},
                                render: function() {
                                    context.drawImage(this.source, this.posc.x, this.posc.y, this.sizes.x, this.sizes.y, this.posscreen.x, this.posscreen.y, this.sizef.x, this.sizef.y);
                                },
                                move: function() {
                                    if(this.posscreen.y + this.sizef.y > 1000) {
                                        aliensBullets.splice(aliensBullets.indexOf(this), 1);
                                    }
                                    this.posscreen.y += 2;
                                    obstaclesItems.some(function(e) {
                                        if(this.posscreen.x > e.posscreen.x - (this.sizef.x/2) && this.posscreen.x < e.posscreen.x + e.sizef.x + (this.sizef.x/2) && this.posscreen.y + this.sizef.y > e.posscreen.y) {
                                            aliensBullets.splice(aliensBullets.indexOf(this), 1);
                                            return true;
                                        }
                                    }.bind(this));
                                    if(this.posscreen.x > player.posscreen.x - (this.sizef.x/2) && this.posscreen.x < player.posscreen.x + player.sizef.x + (this.sizef.x/2) && this.posscreen.y + this.sizef.y > player.posscreen.y) {
                                        player.kill();
                                        aliensBullets.splice(aliensBullets.indexOf(this), 1);
                                    }
                                }
            });
        }
    }
    intervals.splice(intervals.length-1, 1);
    intervals.push(setTimeout(aliensShoot, 2000+(Math.random()*2500)));
}

function loadAliens(image) {
    var speedX = 40;
    for (let j = 0; j < 5; j++) {
        for (let i = 0; i < 8; i++) {
            switch (j) {
                case 0:
                    aliensItems.push({source: image,
                                      score: 200,
                                      poss: {x: 19, y: 134},
                                      posm: {x: 160, y: 134},
                                      sizes: {x: 120, y: 80}
                                    });
                    break;
                case 1:
                    aliensItems.push({source: image,
                                      score: 300,
                                      poss: {x: 19, y: 14},
                                      posm: {x: 165, y: 14},
                                      sizes: {x: 110, y: 80}
                                    });
                    break;
                case 2:
                    aliensItems.push({source: image,
                                      score: 300,
                                      poss: {x: 421, y: 134},
                                      posm: {x: 300, y: 134},
                                      sizes: {x: 100, y: 80}
                                    });
                    break;
                case 3:
                    aliensItems.push({source: image,
                                      score: 400,
                                      poss: {x: 300, y: 134},
                                      posm: {x: 421, y: 134},
                                      sizes: {x: 100, y: 80}
                                    });
                    break;
                case 4:
                    aliensItems.push({source: image,
                                      score: 500,
                                      poss: {x: 312, y: 14},
                                      posm: {x: 428, y: 14},
                                      sizes: {x: 80, y: 80}
                                  });
                    break;
            }
            let rendItem = aliensItems[i+(j*8)];
            rendItem['dead'] = false;
            rendItem['boom'] = true;
            rendItem['sscore'] = false;
            rendItem['sizef'] = {x: rendItem.sizes.x*scale, y: rendItem.sizes.y*scale};
            rendItem['posc'] = {x: rendItem.poss.x, y: rendItem.poss.y};
            rendItem['posscreen'] = {x: (i*(170*scale))+((120*scale-rendItem.sizef.x)/2), y: (600-(j*120))*scale};
            rendItem['render'] = function() {
                if(!this.dead) {
                    context.drawImage(this.source, this.posc.x, this.posc.y, this.sizes.x, this.sizes.y, this.posscreen.x, this.posscreen.y, this.sizef.x, this.sizef.y);
                }else if(this.boom){
                    if(this.sscore) {
                        context.textAlign = "center";
                        context.font = "20px Arial";
                        context.fillStyle = "white";
                        context.fillText(this.score, this.posscreen.x + (this.sizef.x/2), this.posscreen.y + (this.sizef.y/2) + 5);
                    }else{
                        context.drawImage(this.source, 359, 632, 96, 58, this.posscreen.x, this.posscreen.y, this.sizef.x, this.sizef.y);
                    }
                }
            };
            rendItem['move'] = function() {
                if (this.posc.x==this.poss.x&&this.posc.y==this.poss.y) {
                    this.posc.x = this.posm.x; this.posc.y = this.posm.y;
                }else{
                    this.posc.x = this.poss.x; this.posc.y = this.poss.y;
                }
                this.posscreen.x += speedX;
                if ((aliensItems[aliensItems.length-1].posscreen.x + aliensItems[aliensItems.length-1].sizef.x + speedX) > canvas.width || (aliensItems[0].posscreen.x + speedX) < 0) {
                    aliensItems.forEach(function(e) {
                        e.posscreen.y += 40;
                    });
                    if((aliensItems[0].posscreen.x + 2*speedX) < 0) {
                        aliensItems[0].posscreen.x -= 2*speedX;
                        aliensItems.forEach(function(e) {
                            e.posscreen.x += speedX;
                        });
                    }else{
                        aliensItems.forEach(function(e) {
                            e.posscreen.x -= speedX;
                        });
                    }
                    speedX = -speedX;
                }
                if(aliensItems[0].posscreen.y + aliensItems[0].sizef.y > 780) {
                    player.lifes -= player.lifes;
                    player.kill();
                }
            }
            rendItem['kill'] = function() {
                this.dead = true;
                var index = aliensItems.indexOf(this);
                if(frontAliens.indexOf(index) != -1) {
                    if(index < 32) {
                        for(var i=1; i<(5-(index/8)); i++) {
                            if(!aliensItems[index + (8*i)].dead) {
                                frontAliens[frontAliens.indexOf(index)] = index + (8*i);
                                break;
                            }
                        }
                    }else{
                        frontAliens[frontAliens.indexOf(index)] = -1;
                    }
                }
                setTimeout(function() { this.boom = false; }.bind(this), 350);
                setTimeout(function() { this.sscore = true; }.bind(this), 100);
            }
        }
    }
}

function loadObstacles(image) {
    for(var i=0; i<4; i++) {
        obstaclesItems.push({source: image,
                             posc: {x: 368, y: 270},
                             posscreen: {x: (i*350)+380, y: 800},
                             sizes: {x: 104, y: 73},
                             sizef: {x: (104*2)*scalePlayer, y: (73*2)*scalePlayer},
                             render: function() {
                                 context.drawImage(this.source, this.posc.x, this.posc.y, this.sizes.x, this.sizes.y, this.posscreen.x, this.posscreen.y, this.sizef.x, this.sizef.y);
                             }
        });
    }
}

function loadPlayer(image) {
    player = {source: image,
              score: 0,
              bulletsps: 1,
              isShooting: false,
              hitted: false,
              lifes: 3,
              posc: {x: 150, y: 638},
              posscreen: {x: 960, y: 950},
              sizes: {x: 73, y: 52},
              sizef: {x: 73*scalePlayer, y: 52*scalePlayer},
              render: function() {
                  if(!this.hitted) {
                      context.drawImage(this.source, this.posc.x, this.posc.y, this.sizes.x, this.sizes.y, this.posscreen.x, this.posscreen.y, this.sizef.x, this.sizef.y);
                  }else{
                      context.drawImage(this.source, 241, 634, 105, 61, this.posscreen.x, this.posscreen.y, 105*scale, 61*scale);
                  }
              },
              kill: function() {
                  this.hitted = true;
                  deadStop = true;
                  setTimeout(function() {
                      player.hitted = false;
                      deadStop = false;
                  }, 3000);

                  aliensBullets = [];
                  bulletsItem = [];
                  if(this.lifes > 0) {
                      this.lifes -= 1;
                  }else{
                      aliensItems = [];
                      frontAliens = [0, 1, 2, 3, 4, 5, 6, 7];
                      intervals.forEach(function(e) {
                         clearInterval(e);
                      });
                      clear();
                      context.textAlign = "center";
                      context.font = "80px Arial";
                      context.fillStyle = "white";
                      context.fillText("Game Over", canvas.width/2, canvas.height/2 - 50);
                      context.font = "60px Arial";
                      context.fillText("Score: " + player.score, canvas.width/2, canvas.height/2 + 50);
                      setTimeout(init, 3000);
                  }
              }
    };
    document.addEventListener("keydown", function(ev) {
        keyMap[ev.keyCode] = ev.type == 'keydown';
    });
    document.addEventListener("keyup", function(ev) {
        keyMap[ev.keyCode] = ev.type == 'keydown';
    });
    setInterval(function() {
        if(!deadStop) {
            if(keyMap[27]){
                deadStop = true;
            }
            if(keyMap[37]){
                if(player.posscreen.x > 10) {
                    player.posscreen.x -= 5;
                }
            }else if(keyMap[39]){
                if(player.posscreen.x + player.sizef.x < 1910) {
                    player.posscreen.x += 5;
                }
            }
            if(keyMap[38]) {
                if(!player.isShooting) {
                    fire();
                }
            }else if(keyMap[32]) {
                if(!player.isShooting) {
                    fire();
                }
            }
            function fire() {
                bulletsItem.push({posscreen: {x: player.posscreen.x + player.sizef.x/2 -2, y: player.posscreen.y - player.sizef.y/2 - 20},
                                  render: function() {
                                      context.fillStyle = "white";
                                      context.fillRect(this.posscreen.x, this.posscreen.y, 5, 20);
                                  },
                                  move: function() {
                                      if(this.posscreen.y < 0) {
                                          bulletsItem.splice(bulletsItem.indexOf(this), 1);
                                      }
                                      this.posscreen.y -= 10;
                                      let index = bulletsItem.indexOf(this);
                                      obstaclesItems.some(function(e) {
                                          if(this.posscreen.x > e.posscreen.x - 2.5 && this.posscreen.x < e.posscreen.x + e.sizef.x + 2.5 && this.posscreen.y < e.posscreen.y + e.sizef.y) {
                                              bulletsItem.splice(bulletsItem.indexOf(this), 1);
                                              return true;
                                          }
                                      }.bind(this));
                                      if(this.posscreen.y <= aliensItems[0].posscreen.y + aliensItems[0].sizef.y && this.posscreen.y >= aliensItems[39].posscreen.y && this.posscreen.x >= aliensItems[0].posscreen.x && this.posscreen.x <= (aliensItems[7].posscreen.x + aliensItems[7].sizef.x)) {
                                          aliensItems.some(function(e, i) {
                                              if(!e.dead && bulletsItem[index].posscreen.x >= e.posscreen.x && bulletsItem[index].posscreen.x <= e.posscreen.x + e.sizef.x && bulletsItem[index].posscreen.y >= e.posscreen.y && bulletsItem[index].posscreen.y <= e.posscreen.y + e.sizef.y) {
                                                  e.kill();
                                                  var allDead = true;
                                                  aliensItems.some(function(e) { if(!e.dead) { allDead = false; return true; } })
                                                  if(allDead) {
                                                      aliensBullets = [];
                                                      bulletsItem = [];
                                                      aliensItems = [];
                                                      frontAliens = [0, 1, 2, 3, 4, 5, 6, 7];
                                                      intervals.forEach(function(e) {
                                                         clearInterval(e);
                                                      });
                                                      clear();
                                                      context.textAlign = "center";
                                                      context.font = "80px Arial";
                                                      context.fillStyle = "white";
                                                      context.fillText("Winner!!", canvas.width/2, canvas.height/2 - 50);
                                                      context.font = "60px Arial";
                                                      context.fillText("Score: " + player.score, canvas.width/2, canvas.height/2 + 50);
                                                      setTimeout(init, 3000);
                                                  }
                                                  player.score += e.score;
                                                  bulletsItem.splice(bulletsItem.indexOf(this), 1);
                                                  return true;
                                              }
                                          });
                                      }
                                  }
                });
                player.isShooting = true;
                setTimeout(function() { player.isShooting = false; }, 1000/player.bulletsps);
            }
        }else{
            if(keyMap[27]){
                deadStop = false;
            }
        }
    }, 1000/60);
}

function renderHud() {
    context.textAlign = "left";
    context.font = "18pt Arial";
    context.fillStyle = "white";
    //context.fillText(actualFps + " FPS", 20, 50);
    context.font = "30px Arial";
    context.fillStyle = "white";
    context.fillText("Lifes:", 30, 1055);
    context.fillText("Score: " + player.score, 1700, 1055);
    for (var i = 0; i < player.lifes; i++) {
        context.drawImage(player.source, 150, 638, 73, 52, 120+(100*scalePlayer*i), 1020, 73*scalePlayer, 52*scalePlayer);
    }
    context.fillRect(0, 1000, canvas.width, 10);
}
