#!/opt/local/bin/python2.7

# Robot address
robot_mac = '20:14:05:16:21:02'


import sys, math
import lightblue
import pygame, pygame.gfxdraw


# Colors
black = (0,0,0)
dark_gray = (64,64,64)
gray = (127,127,127)
light_gray = (192,192,192)
white = (255,255,255)
red = (255,0,0)
blue = (0,0,255)
bluegreen = (0,128,128)


# Screen config
size = w,h = 600,400
hh = 50
djoyr = int(0.35*(h-hh))
djoyp1 = (w/4,(h-hh)/2)
djoyp2 = (3*w/4,(h-hh)/2)


# Init. pygame
pygame.init()
screen = pygame.display.set_mode(size,pygame.DOUBLEBUF)
pygame.display.set_caption('BlueBot Controller')
font = pygame.font.Font(None,20)
clk = pygame.time.Clock()

# Joystick
#assert pygame.joystick.get_count()>0
#joy = pygame.joystick.Joystick(0)
#joy.init()
#assert joy.get_init()

# Mode
modeD = True


# Aux. func.
def init_bt():
    client_socket = lightblue.socket()
    print >> sys.stderr, 'Contacting the robot...'
    client_socket.connect((robot_mac, 1))
    print >> sys.stderr, 'Connected!'
    return client_socket

def draw_joy((cx,cy),r,(x,y),col):
    pygame.gfxdraw.aacircle(screen,cx,cy,r,light_gray)
    pygame.gfxdraw.aacircle(screen,int(cx+r*x),int(cy+r*y),5,col)
    text = [font.render('x = '+str(x),12,light_gray),font.render('y = '+str(y),12,light_gray),font.render('r = '+str(math.sqrt(x*x+y*y)),12,light_gray),font.render('t = '+str(math.atan2(-y,x)),12,light_gray)] #,font.render(str(int((math.atan2(-y,x)/math.pi+1)*127)),12,red)]
    for i in range(len(text)):
        screen.blit(text[i],(cx-r,cy+r+(i+1)*15))

def draw_screen(j1,j2):
    screen.fill(black)
    text = font.render('Mode '+('D' if modeD else 'S'),16,bluegreen)
    screen.blit(text,(30,20))
    draw_joy(djoyp1,djoyr,j1,blue)
    draw_joy(djoyp2,djoyr,j2,red)
    pygame.display.flip()


# MAIN
def main():
    global modeD
    modeD = (len(sys.argv)==1)
    bt = init_bt()
    draw_screen((0,0),(0,0))
    while True:
        joyEvent = True
        for event in pygame.event.get():
            if event.type==pygame.QUIT or (event.type==pygame.KEYDOWN and event.key==pygame.K_ESCAPE):
                bt.close()
                exit()
            #elif event.type==pygame.JOYBUTTONDOWN:
            #    print >> sys.stderr, [joy.get_button(i) for i in range(joy.get_numbuttons())]
            #elif (event.type==pygame.KEYDOWN and event.key==pygame.K_SPACE) or (event.type==pygame.JOYBUTTONDOWN and joy.get_button(6)):
            #    modeD = not modeD
            elif (event.type==pygame.KEYDOWN and event.key==pygame.K_SPACE):
                joyEvent = False
                bt.send('D'+chr(127)+chr(127))
            elif (event.type==pygame.KEYDOWN and event.key==pygame.K_UP):
                joyEvent = False
                bt.send('D'+chr(254)+chr(127))
            elif (event.type==pygame.KEYDOWN and event.key==pygame.K_DOWN):
                joyEvent = False
                bt.send('D'+chr(0)+chr(127))
            elif (event.type==pygame.KEYDOWN and event.key==pygame.K_RIGHT):
                joyEvent = False
                bt.send('D'+chr(254)+chr(254))
            elif (event.type==pygame.KEYDOWN and event.key==pygame.K_LEFT):
                joyEvent = False
                bt.send('D'+chr(254)+chr(0))
            #elif joyEvent and event.type==pygame.JOYAXISMOTION:
            #    joyEvent = False
            #    ax1 = [joy.get_axis(i) for i in range(2)]
            #    ax2 = [joy.get_axis(i) for i in range(3,5)]
            #    draw_screen(tuple(ax1),tuple(ax2))
            #    if modeD:
            #        bt.send('D'+chr(int((1-ax1[1])*127))+chr(int((ax2[0]+1)*127)))
            #    else:
            #        x,y = ax1[0],-ax1[1]
            #        bt.send('S'+chr(min(int(math.sqrt(x*x+y*y)*255),255))+chr(int((math.atan2(y,x)/math.pi+1)*127)))
        clk.tick(20)
    bt.close()

main()
