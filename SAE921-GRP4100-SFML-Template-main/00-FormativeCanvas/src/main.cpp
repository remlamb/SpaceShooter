#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>  

#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

//Change a sf::Text with a fake signature construct with initials and a number for the Painting
void Signature(sf::Text& signature, sf::Color color) { 
    //create two random character to simulate a Signature, one for the firstname, an other for the lastname. //based on Ascii Table https://www.asciitable.com/
    char firstName = 97 + rand() % 26; 
    char lastName = 97 + rand() % 26;
    std::string fullName;
    fullName.insert(0, 1, lastName); 
    fullName += ".";
    fullName.insert(2, 1, firstName);
    fullName += "/";
    fullName += std::to_string(rand() % 100); //add a random number, like the painting is a part of a series.
    signature.setColor(color);
    signature.setString(fullName);
}

//Set in the vector an amout of rectangle that follow a certain diffusion.  6 set of 30 rectangles that reduce when the y axis change 
void PlotterDrawing(std::vector<sf::RectangleShape>& rectangleCollection, sf::Color redRectangle, bool& firstPainting) {
    rectangleCollection.clear();
    firstPainting = false;
    int currentRectangleToDraw = 50;    //nbr of rectangle to draw at a position
    int currentPosRectangleAdded = 0;   //Rectangle currently added in a certain x position;
    int currentPosXRectangleAdded = 0;    //Rectangle currently added in all the currentx axis;
    int currentPosX = 150;  //use to change the position of created rectangle on X axis
    int currentPosY = 150;  //use to change the position of created rectangle on Y axis

    for (int i = 0; i < 900; i++) {
        sf::RectangleShape newRectangle;
        int dimensionX = rand() % 110 + 20;
        int dimensionY = rand() % 110 + 20;
        newRectangle.setSize(sf::Vector2f(dimensionX, dimensionY));
        newRectangle.setFillColor(sf::Color(0,0,0,0));  //transparent color, we just want the outline 
        newRectangle.setOutlineColor(redRectangle);
        newRectangle.setOutlineThickness(2);

        //if we draw enough rectangle in a pos we go to the next x pos 
        if (currentPosRectangleAdded >= currentRectangleToDraw) {
            currentPosX += 100;
            currentPosRectangleAdded = 0; 
        }

        //if we draw enoug rectangle in the current x row, here 6 times, we change the y pos and return to the first xpos we use, here 100
        if (currentPosXRectangleAdded >= 6 * currentRectangleToDraw) {
            currentPosY += 100;
            currentPosX = 150;
            currentPosRectangleAdded = 0;
            currentPosXRectangleAdded = 0;
            currentRectangleToDraw -= 10;
        }

        newRectangle.setPosition(currentPosX, currentPosY);
        newRectangle.setOrigin(dimensionX / 2, dimensionY / 2);
        newRectangle.rotate(rand() % 25 + -25);
        currentPosRectangleAdded++;
        currentPosXRectangleAdded++;
        rectangleCollection.emplace_back(newRectangle);
    }
}  //red one

//Set in the vector 14 rectangles with differant size and position
void SquareJava(std::vector<sf::RectangleShape>& rectangleCollection, sf::Color lineColor, bool& firstPainting) {
    rectangleCollection.clear();
    for (int i = 0; i < 14; i++) {
        sf::RectangleShape newRectangle;
        newRectangle.setSize(sf::Vector2f(rand() % 300 + 50, rand() % 300 + 50));
        newRectangle.setFillColor(sf::Color(0,0,0,0));  //Transparent, we just want the outline
        newRectangle.setOutlineColor(lineColor);
        newRectangle.setOutlineThickness(5);
        newRectangle.setPosition(rand() % 400 + 200, rand() % 400 + 200);
        newRectangle.setOrigin(newRectangle.getSize().x/2, newRectangle.getSize().y / 2); //origin centered
        rectangleCollection.emplace_back(newRectangle);
        firstPainting = true;
    }
} //grey one

//Create for each rectangle in the vector add an other rectangle that create the illusion of a shadow 
sf::RectangleShape SquareJavaShadowEffect(sf::Color greyShadowRectangle, sf::RectangleShape rectangle) {
    sf::RectangleShape shadowRectangle;
    shadowRectangle.setSize(rectangle.getSize());;
    shadowRectangle.setFillColor(sf::Color(0, 0, 0, 0));
    shadowRectangle.setOutlineColor(greyShadowRectangle);
    shadowRectangle.setOutlineThickness(5);
    shadowRectangle.setOutlineThickness(rectangle.getOutlineThickness());
    shadowRectangle.setPosition(rectangle.getPosition() + sf::Vector2f(20, 20));
    shadowRectangle.setOrigin(shadowRectangle.getSize().x / 2, shadowRectangle.getSize().y / 2);
    return shadowRectangle;
}

int main()
{
    srand(time(NULL));

    //set up antialiasing 
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Painting", 7U, settings);

    //load font use for Signature
    sf::Font font;
    if (!font.loadFromFile("data/font/Thesignature.ttf"))
    {
        std::cout << "font don't load" << std::endl;
    }

    //Color
    sf::Color greyBackground(186, 186, 186);  
    sf::Color greyRectangle(48, 48, 48, 255);
    sf::Color greyShadowRectangle(130, 130, 130);
    sf::Color redRectangle(237, 130, 130, 180);
    
    //Signature, set up the text
    sf::Text signature;
    signature.setFont(font);
    signature.setCharacterSize(60);
    signature.setPosition(650, 700);
    signature.setString("");


    std::vector<sf::RectangleShape> rectangleCollection;
    bool firstPainting = false;


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // Event "Closed" : close window
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                SquareJava(rectangleCollection, greyRectangle, firstPainting);
                Signature(signature, greyShadowRectangle);
                break;

            case sf::Event::KeyPressed:
                PlotterDrawing(rectangleCollection, redRectangle, firstPainting);
                Signature(signature, redRectangle);
                break;

            default:
                break;
            }
        }

        // Graphical Region
        //Clear with the color background, choosen color for each painting. 
        if (firstPainting) {
            window.clear(greyBackground);
            //Only the first painting got a ShadowEffect
            //For each rectangle in the vector we draw his shadow
            for (auto rectangle : rectangleCollection) {
                window.draw(SquareJavaShadowEffect(greyShadowRectangle, rectangle));
            }
        }
        else
        {
            window.clear(sf::Color::White);
        }

        //Draw the vector
        for (auto rectangle : rectangleCollection) {
            window.draw(rectangle);
        }
        window.draw(signature);
        // Window Display
        window.display();

    }
}


