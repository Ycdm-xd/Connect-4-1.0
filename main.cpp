#include <SFML/Graphics.hpp>
#include <iostream>


struct Button
{
    sf::Vector2f fupperLimit, flowerLimit;
    sf::Vector2i iupperLimit, ilowerLimit;
};
struct interactiveButton
{
    sf::RectangleShape shape;
    sf::Texture normal;
    sf::Texture hover;
    sf::Texture special;
    Button button;
};
void unlock(bool &m, bool &h, char cw, short dif)
{
    if (cw=='R')
    {
        if (dif == 3)
            m = 0;
        else if (dif == 5)
            h = 0;
    }
}
void normalize(interactiveButton &ib)
{
    ib.shape.setTexture(&ib.normal);
}
void hoverize(interactiveButton &ib)
{
    ib.shape.setTexture(&ib.hover);
}
void menuReset(interactiveButton &vsPlayer, interactiveButton &vsCOM, interactiveButton &menuExit, bool &movingAtoM, sf::Vector2f menuPos1)
{
    normalize(vsPlayer);
    normalize(vsCOM);
    movingAtoM = 1;
    vsPlayer.shape.setPosition(menuPos1.x, -200);
    vsCOM.shape.setPosition(menuPos1.x, -200);
    menuExit.shape.setPosition(menuPos1.x, -200);
}
void manageGridMap(bool &mapToggle, char gridMap[6][7], short &currentColumnCounter, short &i)
{
    if (mapToggle)
    {
        gridMap[currentColumnCounter][i]='R';
        mapToggle=0;
    }
    else
    {
        gridMap[currentColumnCounter][i]='Y';
        mapToggle=1;
    }
    for (short i=0; i<6; ++i)
    {
        for (short j=0; j<7; ++j)
            std::cout<<gridMap[i][j]<<' ';
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void pvpAnnounceWin(char currentWinner, bool &movingSub, bool &win, sf::Sprite &winShape, sf::Sprite redWinSprite, sf::Sprite yellowWinSprite)
{
    movingSub = 1;
    win=1;
    switch (currentWinner)
    {
    case 'R':
        winShape = redWinSprite;
        break;
    case 'Y':
        winShape = yellowWinSprite;
        break;
    case 'T':
        // do stuff
        break;
    }
}
void pvpDraw(sf::RenderWindow &window, sf::RectangleShape inGamebackgroundShape, sf::RectangleShape Chip[42], sf::RectangleShape grid, interactiveButton mainMenu, bool win, sf::RectangleShape subMenuShape, sf::Sprite winShape, bool movingSub, interactiveButton playAgain, interactiveButton dontPlayAgain)
{
    window.draw(inGamebackgroundShape);
    for (short i=41; i>=0; --i)
        window.draw(Chip[i]);
    window.draw(grid);
    window.draw(mainMenu.shape);
    if (win)
    {
        window.draw(subMenuShape);
        window.draw(winShape);
        if (movingSub==0)
        {
            window.draw(playAgain.shape);
            window.draw(dontPlayAgain.shape);
        }
    }
}
void reset (sf::RectangleShape Chip[42], short CC[7], short &Cur, char matrix[6][7], bool &win, bool &mapToggle)
{
    win = 0;
    mapToggle = 1;
    Cur = 0;
    for (short i=0; i<42; ++i)
    {
        if (i<7)
            CC[i]=0;
        if (i%2==0)
                Chip[i].setPosition(1180, 590 - (i*8));
        else
                Chip[i].setPosition(1280, 590 - ((i-1)*8));
    }

    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
            matrix[i][j]='e';
}
void hang()
{
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        continue;
}
bool LMB()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return 1;
    else
        return 0;
}
void RectButtonAssign (sf::RectangleShape RShape, Button &RButton)
{
    RButton.flowerLimit = RShape.getPosition();
    RButton.fupperLimit.x = RButton.flowerLimit.x + RShape.getSize().x;
    RButton.fupperLimit.y = RButton.flowerLimit.y + RShape.getSize().y;
}
void RectButtonAssign2 (interactiveButton &ib)
{
    ib.button.flowerLimit = ib.shape.getPosition();
    ib.button.fupperLimit.x = ib.button.flowerLimit.x + ib.shape.getSize().x;
    ib.button.fupperLimit.y = ib.button.flowerLimit.y + ib.shape.getSize().y;
}
bool isButtonHoveredf2 (Button AButton, sf::Vector2i original)
{
    if (original.x<AButton.fupperLimit.x && original.x>AButton.flowerLimit.x && original.y<AButton.fupperLimit.y && original.y>AButton.flowerLimit.y)
        return 1;
    else
        return 0;
}
bool isButtonHoveredf3 (Button AButton, sf::RenderWindow &window)
{
    sf::Vector2i original = sf::Mouse::getPosition(window);
    if (original.x<AButton.fupperLimit.x && original.x>AButton.flowerLimit.x && original.y<AButton.fupperLimit.y && original.y>AButton.flowerLimit.y)
        return 1;
    else
        return 0;
}
bool isButtonHoveredf4 (interactiveButton ib, sf::RenderWindow &window)
{
    Button AButton = ib.button;
    sf::Vector2i original = sf::Mouse::getPosition(window);
    if (original.x<AButton.fupperLimit.x && original.x>AButton.flowerLimit.x && original.y<AButton.fupperLimit.y && original.y>AButton.flowerLimit.y)
        return 1;
    else
        return 0;
}
bool ibuttonAutoHover (interactiveButton &ib, sf::RenderWindow &window)
{
    if (isButtonHoveredf4(ib, window))
    {
        hoverize(ib);
        if (LMB())
            return 1;
    }
    else
        normalize(ib);
    return 0;
}
void muteCheck(Button muteButton, sf::RenderWindow &window, bool &muted, sf::RectangleShape &muteShape, sf::Texture &mute, sf::Texture &unmute)
{
    if (LMB() && isButtonHoveredf3(muteButton, window))
    {
        if (muted)
        {
            muted = 0;
            muteShape.setTexture(&unmute);
        }
        else
        {
            muted = 1;
            muteShape.setTexture(&mute);
        }
        hang();
    }
}
bool yMovingR (sf::RectangleShape &RS, sf::Vector2f destination, char direction, float speed)
{
    if (direction=='d')
    {
        if (RS.getPosition().y>=destination.y)
        {
            RS.setPosition(destination);
            return 0;
        }
        else
        {
            RS.move(0, speed);
            return 1;
        }
    }
    else if (direction=='u')
    {
        if (RS.getPosition().y<=destination.y)
        {
            RS.setPosition(destination);
            return 0;
        }
        else
        {
            RS.move(0, -1.0*speed);
            return 1;
        }
    }
}
bool yMovingS (sf::Sprite &RS, sf::Vector2f destination, char direction, float speed)
{
    if (direction=='d')
    {
        if (RS.getPosition().y>=destination.y)
        {
            RS.setPosition(destination);
            return 0;
        }
        else
        {
            RS.move(0, speed);
            return 1;
        }
    }
    else if (direction=='u')
    {
        if (RS.getPosition().y<=destination.y)
        {
            RS.setPosition(destination);
            return 0;
        }
        else
        {
            RS.move(0, -1.0*speed);
            return 1;
        }
    }
}
char winner(char matrix[6][7])
{
    // Win By Rows
    for (short i=0; i<6; ++i)
        for (short j=0; j<4; ++j)
            if (matrix[i][j]!='e' && matrix[i][j]==matrix[i][j+1] && matrix[i][j]==matrix[i][j+2] && matrix[i][j]==matrix[i][j+3])
                return matrix[i][j];


    // Win By Diagonals
    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
        {
            if (matrix[i][j]!='e' && i+3<6 && j+3<7 && matrix[i][j]==matrix[i+1][j+1] && matrix[i][j]==matrix[i+2][j+2] && matrix[i][j]==matrix[i+3][j+3])
                return matrix[i][j];
            else if (matrix[i][j]!='e' && i+3<6 && j-3>=0 && matrix[i][j]==matrix[i+1][j-1] && matrix[i][j]==matrix[i+2][j-2] && matrix[i][j]==matrix[i+3][j-3])
                return matrix[i][j];
        }


    // Win By Columns
    for (short i=0; i<3; ++i)
        for (short j=0; j<7; ++j)
            if (matrix[i][j]!='e' && matrix[i][j]==matrix[i+1][j] && matrix[i][j]==matrix[i+2][j] && matrix[i][j]==matrix[i+3][j])
                return matrix[i][j];


    // No win yet
    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
            if (matrix[i][j]=='e')
                return 'e';

    // Tie
    return 'T';
}
bool playTurn (char m[6][7], short col)
{
    short RCounter=0, YCounter=0;

    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
        {
            if (m[i][j]=='R')
                ++RCounter;
            else if (m[i][j]=='Y')
                ++YCounter;
        }

    if (col<0 || col>6 || RCounter+YCounter==42)
        return 0;
    char curTurn = (RCounter==YCounter)? 'R': 'Y';
    for (short i=0; i<6; ++i)
    {
        if (m[i][col]=='e')
        {
            m[i][col] = curTurn;
            return 1;
        }
    }

    return 0;
}
void unplayTurn (char m[6][7], short col)
{
    for (short i=5; i>=0; --i)
    {
        if (m[i][col]!='e')
        {
            m[i][col] = 'e';
            break;
        }
    }
}
short evaluate (char matrix[6][7])
{
    short score=0;


    // Win By Rows
    for (short i=0; i<6; ++i)
        for (short j=0; j<4; ++j)
            if (matrix[i][j]!='e' && matrix[i][j]==matrix[i][j+1] && matrix[i][j]==matrix[i][j+2] && matrix[i][j]==matrix[i][j+3])
            {
                if (matrix[i][j]=='R')
                    score-=3;
                else
                    score+=1;
            }


    // Win By Diagonals
    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
        {
            if (matrix[i][j]!='e' && i+3<6 && j+3<7 && matrix[i][j]==matrix[i+1][j+1] && matrix[i][j]==matrix[i+2][j+2] && matrix[i][j]==matrix[i+3][j+3])
            {
                if (matrix[i][j]=='R')
                    score-=3;
                else
                    score+=1;
            }
            else if (matrix[i][j]!='e' && i+3<6 && j-3>=0 && matrix[i][j]==matrix[i+1][j-1] && matrix[i][j]==matrix[i+2][j-2] && matrix[i][j]==matrix[i+3][j-3])
            {
                if (matrix[i][j]=='R')
                    score-=3;
                else
                    score+=1;
            }
        }


    // Win By Columns
    for (short i=0; i<3; ++i)
        for (short j=0; j<7; ++j)
            if (matrix[i][j]!='e' && matrix[i][j]==matrix[i+1][j] && matrix[i][j]==matrix[i+2][j] && matrix[i][j]==matrix[i+3][j])
            {
                if (matrix[i][j]=='R')
                    score-=3;
                else
                    score+=1;
            }
    //std::cout<<score<<' ';
    return score;
}
void MiniMax (char m[6][7], short level, short &i, long &tracker, long score[])
{
        if (level > 0)
        {
            for (short j=0; j<7; ++j)
            {
                if (playTurn(m, j))
                {
                    score[i]+=evaluate(m);
                    MiniMax(m, level-1, i, tracker, score);
                    unplayTurn(m, j);
                }
            }
        }
        else if (level==0)
        {
            score[i]+=evaluate(m);
        }
}
short COM(char m[6][7], short level)
{
    short maxi=3;
    long score[7] = {0}, maxScore= -99999999999999999, tracker=0;
    for (short i=0; i<7; ++i)
    {
        if (playTurn(m, i))
        {
            score[i]+=evaluate(m);
            MiniMax(m, level-1, i, tracker, score);
            unplayTurn(m, i);
        }
    }

    for (short i=0; i<7; ++i)
    {
        if (score[i] > maxScore && playTurn(m, i)==1)
        {
            unplayTurn(m, i);
            maxScore = score[i];
            maxi = i;
        }
    }

    if (playTurn(m, maxi))
    {
        unplayTurn(m, maxi);
        return maxi;
    }
    else
    {
        for (short i=0; i<7; ++i)
        {
            if (playTurn(m, i))
            {
                unplayTurn(m, i);
                return i;
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1366,690), "Connect 4");

    // gridMap and algorithm related stuff
    char currentWinner='e';
    bool win=0;
    bool mapToggle = 1;
    char gridMap[6][7];
    for (short i=0; i<6; ++i)
        for (short j=0; j<7; ++j)
            gridMap[i][j]='e';



    // Backgrounds
    sf::Texture inGameBackgroundTexture;
    inGameBackgroundTexture.loadFromFile("c1584.png");
    sf::Texture menuBackgroundTexture;
    menuBackgroundTexture.loadFromFile("Back-Menu.png");

    sf::RectangleShape inGamebackgroundShape;
    sf::RectangleShape menuBackgroundShape;

    menuBackgroundShape.setTexture(&menuBackgroundTexture);
    menuBackgroundShape.setSize(sf::Vector2f(1366,690));
    menuBackgroundShape.setPosition(0, 0);

    inGamebackgroundShape.setTexture(&inGameBackgroundTexture);
    inGamebackgroundShape.setSize(sf::Vector2f(1366,690));
    inGamebackgroundShape.setPosition(0, 0);

    // Default Vectors or Positions (for movement)

    sf::Vector2f subMenuDef(233, 245);
    sf::Vector2f winShapeDef(150, 100);
    sf::Vector2f menuButtons(468, 86);
    sf::Vector2f menuPos1(449, 250);
    sf::Vector2f menuPos2(449, 400);
    sf::Vector2f menuPos3(449, 550);


    // Menu and in-game buttons

    interactiveButton vsPlayer, vsCOM, menuExit, mainMenu, playAgain, dontPlayAgain, easy, medium, hard;

    sf::Texture title;
    sf::Texture redWin;
    sf::Texture yellowWin;
    sf::Texture tieWin;
    sf::Texture mute;
    sf::Texture unmute;
    sf::Texture subMenu;

    vsPlayer.normal.loadFromFile("Red_1v1.png");
    vsPlayer.hover.loadFromFile("1_v1_hover.png");
    vsCOM.normal.loadFromFile("1_v_computer.png");
    vsCOM.hover.loadFromFile("1_v_computer_hover.png");
    menuExit.normal.loadFromFile("EXIT.png");
    menuExit.hover.loadFromFile("EXIT_hover.png");
    mainMenu.normal.loadFromFile("MainMenu.png");
    mainMenu.hover.loadFromFile("MainMenu_hover.png");
    playAgain.normal.loadFromFile("Play_Again.png");
    playAgain.hover.loadFromFile("Play_Again_hover_.png");
    easy.normal.loadFromFile("Easy.png");
    easy.hover.loadFromFile("EasyHov.png");
    medium.normal.loadFromFile("Medium.png");
    medium.hover.loadFromFile("MediumHov.png");
    medium.special.loadFromFile("MediumLocked.png");
    hard.normal.loadFromFile("Hard.png");
    hard.hover.loadFromFile("HardHov.png");
    hard.special.loadFromFile("HardLocked.png");
    dontPlayAgain.normal = mainMenu.normal;
    dontPlayAgain.hover = mainMenu.hover;


    title.loadFromFile("title.png");
    mute.loadFromFile("Mute.png");
    unmute.loadFromFile("Unmute.png");
    redWin.loadFromFile("RED_WIN.png");
    yellowWin.loadFromFile("YELLOW_WIN.png");
    subMenu.loadFromFile("WinWindow.png");
    //tieWin.loadFromFile(" ");



    sf::Sprite redWinSprite(redWin);
    sf::Sprite yellowWinSprite(yellowWin);
    sf::RectangleShape titleShape;
    sf::RectangleShape muteShape;
    sf::RectangleShape subMenuShape;

    vsPlayer.shape.setSize(menuButtons);
    vsCOM.shape.setSize(menuButtons);
    menuExit.shape.setSize(menuButtons);
    mainMenu.shape.setSize(sf::Vector2f(200, 40));
    playAgain.shape.setSize(sf::Vector2f(468, 86));
    dontPlayAgain.shape.setSize(sf::Vector2f(468, 86));
    easy.shape.setSize(menuButtons);
    medium.shape.setSize(menuButtons);
    hard.shape.setSize(menuButtons);

    titleShape.setSize(menuButtons);
    muteShape.setSize(sf::Vector2f(60,60));
    subMenuShape.setSize(sf::Vector2f (900,400));

    normalize(vsPlayer);
    normalize(vsCOM);
    normalize(menuExit);
    normalize(mainMenu);
    normalize(playAgain);

    easy.shape.setTexture(&easy.normal);
    medium.shape.setTexture(&medium.special);
    hard.shape.setTexture(&hard.special);

    titleShape.setTexture(&title);
    muteShape.setTexture(&unmute);
    subMenuShape.setTexture(&subMenu);

    vsPlayer.shape.setPosition(menuPos1);
    vsCOM.shape.setPosition(menuPos2);
    menuExit.shape.setPosition(menuPos3);
    mainMenu.shape.setPosition(20, 20);
    playAgain.shape.setPosition(450, 370);
    dontPlayAgain.shape.setPosition(450, 470);
    easy.shape.setPosition(menuPos1);
    medium.shape.setPosition(menuPos2);
    hard.shape.setPosition(menuPos3);

    titleShape.setPosition(449, 100);
    muteShape.setPosition(1280, 30);
    subMenuShape.setPosition(subMenuDef);
    redWinSprite.setPosition(winShapeDef);
    yellowWinSprite.setPosition(winShapeDef);

    Button muteButton;

    RectButtonAssign(muteShape, muteButton);

    RectButtonAssign2(vsPlayer);
    RectButtonAssign2(vsCOM);
    RectButtonAssign2(menuExit);
    RectButtonAssign2(mainMenu);
    RectButtonAssign2(playAgain);
    RectButtonAssign2(dontPlayAgain);
    RectButtonAssign2(easy);
    RectButtonAssign2(medium);
    RectButtonAssign2(hard);


    // Button Motion
    vsPlayer.shape.setPosition(menuPos1.x, -200);
    vsCOM.shape.setPosition(menuPos1.x, -200);
    menuExit.shape.setPosition(menuPos1.x, -200);


    // Chips
    float chipRadius = 43.5;
    sf::Texture yellowChip;
    sf::Texture redChip;
    yellowChip.loadFromFile("yellownew.png");
    redChip.loadFromFile("rednew.png");
    sf::RectangleShape Chip[42];
    for (short i=0; i<42; ++i)
    {
        Chip[i].setSize(sf::Vector2f (chipRadius*2, chipRadius*2));
        if (i%2==0)
            {
                Chip[i].setTexture(&redChip);
                Chip[i].setPosition(1180, 590 - (i*8));
            }
        else
            {
                Chip[i].setTexture(&yellowChip);
                Chip[i].setPosition(1280, 590 - ((i-1)*8));
            }
        Chip[i].setOrigin(chipRadius,chipRadius);
    }


    // Grid
    sf::RectangleShape grid;
    grid.setSize(sf::Vector2f(800, 600));
    sf::Texture gridTexture;
    gridTexture.loadFromFile("gridwoutline.png");
    grid.setTexture(&gridTexture);
    grid.setPosition(283,90);


    // Grid Positions as Vector2f
    sf::Vector2f gridPos[6][7];
    gridPos[0][0].x = 283 + 95.7;
    gridPos[0][0].y = 690 - 75;
    for (short i=0; i<6; ++i)
    {
        for (short j=0; j<7; ++j)
        {
            gridPos[i][j].x = gridPos[0][0].x + (j*101.5);
            gridPos[i][j].y = gridPos[0][0].y - (i*94.7);
        }
    }

    sf::Vector2f gridHoverPos[7];
    for (short i=0; i<7; ++i)
    {
        gridHoverPos[i]=gridPos[5][i];
        gridHoverPos[i].y -= 95;
    }





    // Column Buttons
    float columnSpacing = 102;
    Button Column[7];
    Column[0].flowerLimit = grid.getPosition();
    Column[0].flowerLimit.x += 42;
    Column[0].fupperLimit = Column[0].flowerLimit;
    Column[0].fupperLimit.y += 600;
    Column[0].fupperLimit.x += columnSpacing;
    for (short i=1; i<7; ++i)
    {
        Column[i].flowerLimit = Column[0].flowerLimit;
        Column[i].flowerLimit.x += (i*columnSpacing);
        Column[i].fupperLimit = Column[0].fupperLimit;
        Column[i].fupperLimit.x += (i*columnSpacing);
    }




    // Variables for Runtime use and calculations on the go
    short currentChip=0, columnCounter[7]={0}, difficulty;
    char currentMode = 'M', destinationMode;
    bool muted = 0, mediumLocked = 1, hardLocked = 1;
    bool movingChip = 0, movingSub = 0, movingMtoD = 0, movingAtoM = 1;
    sf::Vector2f destination;
    sf::Sprite winShape;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }



        muteCheck(muteButton, window, muted, muteShape, mute, unmute);

        currentWinner=winner(gridMap);

        switch (currentMode)
        {
            case 'G':
                if (movingChip)
                {
                    if (yMovingR(Chip[currentChip], destination, 'd', 2.3)==0)
                    {
                        movingChip = 0;
                        if (currentChip<41)
                            ++currentChip;
                    }
                }
                else if (win)
                {
                    if (movingSub)
                    {
                        if (yMovingR(subMenuShape, subMenuDef, 'u', 1.7)==0 && yMovingS(winShape, winShapeDef, 'd', 1.7)==0)
                            movingSub = 0;
                    }
                    else
                    {
                        if (ibuttonAutoHover(playAgain, window))
                        {
                            reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                            hang();
                        }
                        else if (ibuttonAutoHover(dontPlayAgain, window))
                        {
                            currentMode = 'B';
                            menuBackgroundShape.setPosition(0, 690);
                            destinationMode = 'M';
                            menuReset(vsPlayer, vsCOM, menuExit, movingAtoM, menuPos1);
                            reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                            hang();
                        }
                    }
                }
                else if (currentWinner!='e')
                {
                    pvpAnnounceWin(currentWinner, movingSub, win, winShape, redWinSprite, yellowWinSprite);
                    subMenuShape.setPosition(subMenuDef.x, 900);
                    winShape.setPosition(winShapeDef.x, -330);
                }
                else
                {
                    if (currentChip!=41)
                        Chip[currentChip].setPosition(1500, 0);
                    for (short i=0; i<7; ++i)
                    {
                        if (columnCounter[i]<6  &&  isButtonHoveredf3(Column[i], window))
                        {
                            Chip[currentChip].setPosition(gridHoverPos[i]);
                            if (LMB())
                            {
                                short currentColumnCounter = columnCounter[i]++;
                                destination = gridPos[currentColumnCounter][i];
                                movingChip=1;
                                manageGridMap(mapToggle, gridMap, currentColumnCounter, i);
                                hang();
                            }
                        }
                    }
                }

                if (ibuttonAutoHover(mainMenu, window))
                {
                    currentMode = 'B';
                    menuBackgroundShape.setPosition(0, 690);
                    destinationMode = 'M';
                    menuReset(vsPlayer, vsCOM, menuExit, movingAtoM, menuPos1);
                    normalize(mainMenu);
                    reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                    hang();
                }
                break;

            case 'M':
                if (movingAtoM)
                {
                    if (yMovingR(vsPlayer.shape, menuPos1, 'd', 2.5)==0 && yMovingR(vsCOM.shape, menuPos2, 'd', 2.5)==0 && yMovingR(menuExit.shape, menuPos3, 'd', 2.5)==0)
                    {
                        movingAtoM = 0;
                    }
                }
                else if (ibuttonAutoHover(vsPlayer, window))
                {
                    currentMode = 'F';
                    inGamebackgroundShape.setPosition(0, -690);
                    destinationMode = 'G';
                    hang();
                }
                else if (ibuttonAutoHover(vsCOM, window))
                {
                    currentMode = 'D';
                    movingMtoD = 1;
                    easy.shape.setPosition(menuPos1.x, -200);
                    medium.shape.setPosition(menuPos1.x, -200);
                    hard.shape.setPosition(menuPos1.x, -200);
                    hang();
                }
                else if (ibuttonAutoHover(menuExit, window))
                {
                        window.close();
                }
                break;
            case 'D':
                if (movingMtoD)
                {
                    if (yMovingR(easy.shape, menuPos1, 'd', 2)==0 && yMovingR(medium.shape, menuPos2, 'd', 2)==0 && yMovingR(hard.shape, menuPos3, 'd', 2)==0)
                    {
                        movingMtoD = 0;
                    }
                }
                else if (ibuttonAutoHover(easy, window))
                {
                    currentMode = 'F';
                    inGamebackgroundShape.setPosition(0, -690);
                    destinationMode = 'C';
                    difficulty = 3;
                    hang();
                }
                else if (mediumLocked==0 && ibuttonAutoHover(medium, window))
                {
                    currentMode = 'F';
                    inGamebackgroundShape.setPosition(0, -690);
                    destinationMode = 'C';
                    difficulty = 5;
                    hang();
                }
                else if (hardLocked==0 && ibuttonAutoHover(hard, window))
                {
                    currentMode = 'F';
                    inGamebackgroundShape.setPosition(0, -690);
                    destinationMode = 'C';
                    difficulty = 7;
                    hang();
                }
                else if (ibuttonAutoHover(mainMenu, window))
                {
                    currentMode = 'M';
                    menuReset(vsPlayer, vsCOM, menuExit, movingAtoM, menuPos1);
                    normalize(mainMenu);
                    hang();
                }
                break;

            case 'F':
                if (yMovingR(inGamebackgroundShape, sf::Vector2f(0.0, 0.0), 'd', 0.7)==0 || yMovingR(menuBackgroundShape, sf::Vector2f(0.0, 690.0), 'd', 0.7)==0)
                {
                    currentMode = destinationMode;
                    menuBackgroundShape.setPosition(0, 0);
                }
                break;
            case 'B':
                if (yMovingR(inGamebackgroundShape, sf::Vector2f(0.0, -690), 'u', 0.7)==0 || yMovingR(menuBackgroundShape, sf::Vector2f(0.0, 0), 'u', 0.7)==0)
                {
                    currentMode = destinationMode;
                    inGamebackgroundShape.setPosition(0, 0);
                }
                break;

            case 'C':
                if (movingChip)
                {
                    if (yMovingR(Chip[currentChip], destination, 'd', 2.3)==0)
                    {
                        movingChip = 0;
                        if (currentChip<41)
                            ++currentChip;
                    }
                }
                else if (win)
                {
                    if (movingSub)
                    {
                        if (yMovingR(subMenuShape, subMenuDef, 'u', 1.7)==0 && yMovingS(winShape, winShapeDef, 'd', 1.7)==0)
                            movingSub = 0;
                    }
                    else
                    {
                        if (ibuttonAutoHover(playAgain, window))
                        {
                            reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                            hang();
                        }
                        else if (ibuttonAutoHover(dontPlayAgain, window))
                        {
                            currentMode = 'B';
                            menuBackgroundShape.setPosition(0, 690);
                            destinationMode = 'M';
                            menuReset(vsPlayer, vsCOM, menuExit, movingAtoM, menuPos1);
                            reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                            hang();
                        }
                    }
                }
                else if (currentWinner!='e')
                {
                    pvpAnnounceWin(currentWinner, movingSub, win, winShape, redWinSprite, yellowWinSprite);
                    subMenuShape.setPosition(subMenuDef.x, 900);
                    winShape.setPosition(winShapeDef.x, -330);
                    unlock(mediumLocked, hardLocked, currentWinner, difficulty);
                }
                else
                {
                    if (currentChip!=41)
                        Chip[currentChip].setPosition(1500, 0);
                    for (short i=0; i<7; ++i)
                    {
                        if (mapToggle==0  || (columnCounter[i]<6  &&  isButtonHoveredf3(Column[i], window)))
                        {
                            if (mapToggle==0)
                                i=COM(gridMap, difficulty);
                            Chip[currentChip].setPosition(gridHoverPos[i]);
                            if (LMB() || mapToggle==0)
                            {
                                short currentColumnCounter = columnCounter[i]++;
                                destination = gridPos[currentColumnCounter][i];
                                movingChip=1;
                                manageGridMap(mapToggle, gridMap, currentColumnCounter, i);
                                hang();
                                break;
                            }
                        }
                    }
                }

                if (ibuttonAutoHover(mainMenu, window))
                {
                    currentMode = 'B';
                    menuBackgroundShape.setPosition(0, 690);
                    destinationMode = 'M';
                    menuReset(vsPlayer, vsCOM, menuExit, movingAtoM, menuPos1);
                    normalize(mainMenu);
                    reset(Chip, columnCounter, currentChip, gridMap, win, mapToggle);
                    hang();
                }
                break;
        }







        window.clear(sf::Color::White);


        switch (currentMode)
        {
            case 'G':
                pvpDraw(window, inGamebackgroundShape, Chip, grid, mainMenu, win, subMenuShape, winShape, movingSub, playAgain, dontPlayAgain);
                break;
            case 'M':
                window.draw(menuBackgroundShape);
                window.draw(vsPlayer.shape);
                window.draw(vsCOM.shape);
                window.draw(menuExit.shape);
                window.draw(titleShape);
                break;
            case 'D':
                window.draw(menuBackgroundShape);
                window.draw(mainMenu.shape);
                window.draw(titleShape);
                window.draw(easy.shape);
                window.draw(medium.shape);
                window.draw(hard.shape);
                break;
            case 'F':
                window.draw(menuBackgroundShape);
                window.draw(inGamebackgroundShape);
                break;
            case 'B':
                window.draw(inGamebackgroundShape);
                window.draw(menuBackgroundShape);
                break;
            case 'C':
                pvpDraw(window, inGamebackgroundShape, Chip, grid, mainMenu, win, subMenuShape, winShape, movingSub, playAgain, dontPlayAgain);
                break;
        }

        window.draw(muteShape);


        window.display();
    }

    return 0;
}
