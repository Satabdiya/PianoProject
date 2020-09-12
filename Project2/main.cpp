#include "stdafx.h"
using namespace sf;
namespace fs = std::experimental::filesystem;

// This returns the filename of the note corresponding the key
std::string playForMe(char letter)
{
	std::string file;

	// These are the filenames that will be returned based on variable letter
	if (letter == 'a') // c3
	{
		file = "1 C3.wav";
	}
	else if (letter == 'z') // c3# or d3b
	{
		file = "2 C3 Sharp D3 Flat.wav";
	}
	else if (letter == 's') // d3
	{
		file = "3 D3.wav";
	}
	else if (letter == 'x') // d3# or e3b
	{
		file = "4 D3 Sharp E3 Flat.wav";
	}
	else if (letter == 'd') // e3
	{
		file = "5 E3.wav";
	}
	else if (letter == 'f') // f3
	{
		file = "6 F3.wav";
	}
	else if (letter == 'v') // f3# or g3b
	{
		file = "7 F3 Sharp G3 Flat.wav";
	}
	else if (letter == 'g') // g3
	{
		file = "8 G3.wav";
	}
	else if (letter == 'b') // g3# or a3b
	{
		file = "9 G3 Sharp A3 Flat.wav";
	}
	else if (letter == 'h') // a3
	{
		file = "10 A3.wav";
	}
	else if (letter == 'n') // a3# or b3b
	{
		file = "11 A3 Sharp B3 Flat.wav";
	}
	else if (letter == 'j') // b3
	{
		file = "12 B3.wav";
	}
	else if (letter == 'k') // c4
	{
		file = "13 C4.wav";
	}

	return file;
}

// This is the function that plays any saved file
void Play()
{
	int width_dialog = 300, height_dialog = 600;
	std::string word; // The user inputted file name

	RenderWindow window(VideoMode(width_dialog, height_dialog),
		"Play", Style::Default);

	// Creates Select Button
	RectangleShape rectangle(Vector2f(100.f, 30.f));
	rectangle.setPosition(190.f, height_dialog - 50.f);
	rectangle.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectSave(190, height_dialog - 50, 100, 30);

	// This is the text box
	RectangleShape textBox(Vector2f(175.f, 30.f));
	textBox.setPosition(5.f, height_dialog - 50.f);
	textBox.setFillColor(Color::White);// Color Light Grey

	// This loads the font
	Font MyFont;
	if (!MyFont.loadFromFile
	("lucidabrightitalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 20); // This creates a Text object
	Text user("", MyFont, 15); // This is the user text display
	user.setColor(Color::Black);

	// This block gets all the filenames that can be played
	std::vector<std::string> file_names;
	std::string path_string(".");
	for (auto& p : fs::recursive_directory_iterator(path_string))
	{
		fs::path path = p.path();
		for (auto &c : path_string)
			c = tolower(c);
		std::string extension_string = p.path().extension().string();
		for (auto &c : extension_string)
			c = tolower(c);

		// This ommits the file created during the program by the programmer
		if (extension_string == ".txt" && p.path().filename().string()
			!= "programsaves.txt")
		{
			// This creates a vector of all the file names available
			file_names.push_back(p.path().filename().string());
		}
	}

	while (window.isOpen())
	{
		Event evnt;

		// This loop runs everytime the user does something
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			// This closes the window if the user clicks the close button
			case Event::Closed:
				window.close();
				break;

			case Event::TextEntered:
			{
				// This adds each letter to the display that the user types
				word += evnt.text.unicode;
				user.setString(word);
				user.setPosition(10.f, height_dialog - 47.f);
			}
			break;

			// This plays the selected song when the Select Button is pressed
			case Event::MouseButtonPressed:

				if (rectSave.contains(Mouse::getPosition(window)))
				{
					bool is_file_error = true;
					word += ".txt"; // This adds the file extension

					// This checks if the filename exists
					for (int i = 0; i < file_names.size(); i++)
					{
						if (file_names[i] == word)
							is_file_error = false;
					}

					// Runs if file is non_existent
					if (is_file_error)
					{
						std::cout << "File does not exist, please re-type";
						word = "";
						user.setString(word);
						user.setPosition(10.f, height_dialog - 47.f);
					}

					// Runs if file exists
					else
					{
						std::ifstream fin(word);
						std::string line, time;
						int index;
						Clock clock;
						SoundBuffer buffer1;
						SoundBuffer buffer2;
						SoundBuffer buffer3;
						SoundBuffer buffer4;
						SoundBuffer buffer5;
						Sound sound1;
						Sound sound2;
						Sound sound3;
						Sound sound4;
						Sound sound5;
						int tracks = 1;
						std::string file;

						// This plays the recording for a set time
						while (std::getline(fin, line))
						{
								index = line.find(" ");
								time = line.substr(0, index);

								// This delays the playing of the track
								// based on the time stamp
								while (clock.getElapsedTime().asSeconds() 
									   <= std::stof(time))
								{
								}

								// This block loads and plays the sound
								std::string character = line.substr(index + 1);
								if (character.length() < 4)
								{
									file = playForMe(std::stoi(character));
									if (tracks == 1)
									{
										if (!buffer1.loadFromFile(file))
										{
											std::cout << file
												<< " ERROR: Loading Sound Effect"
												<< std::endl;
										}
										sound1.setBuffer(buffer1);
										sound1.play();
										tracks = 2;
									}
									else if (tracks == 2)
									{
										if (!buffer2.loadFromFile(file))
										{
											std::cout << file
												<< " ERROR: Loading Sound Effect"
												<< std::endl;
										}
										sound2.setBuffer(buffer2);
										sound2.play();
										tracks = 3;
									}
									else if (tracks == 3)
									{
										if (!buffer3.loadFromFile(file))
										{
											std::cout << file
												<< " ERROR: Loading Sound Effect"
												<< std::endl;
										}
										sound3.setBuffer(buffer3);
										sound3.play();
										tracks = 4;
									}
									else if (tracks == 4)
									{
										if (!buffer4.loadFromFile(file))
										{
											std::cout << file
												<< " ERROR: Loading Sound Effect"
												<< std::endl;
										}
										sound4.setBuffer(buffer4);
										sound4.play();
										tracks = 5;
									}
									if (tracks == 5)
									{
										if (!buffer5.loadFromFile(file))
										{
											std::cout << file
												<< " ERROR: Loading Sound Effect"
												<< std::endl;
										}
										sound5.setBuffer(buffer5);
										sound5.play();
										tracks = 1;
									}
								}
						}
						window.close();
					}
				}
				break;
			}
		}
		window.clear();

		text.setColor(Color::White);
		text.setString("Please select one of these files:");
		text.setPosition(5, 30);
		window.draw(text);

		// This draws all the file names
		text.setCharacterSize(15);
		for (int i = 0, x = 60; i < file_names.size(); i++)
		{
			text.setString
			(file_names[i].substr(0, (file_names[i].length() - 4)));

			text.setPosition(5, x);
			window.draw(text);
			x += 20;
		}

		// This creates the Select Button
		text.setCharacterSize(20);
		text.setColor(Color::Black);
		window.draw(rectangle);
		text.setString("Select");
		text.setPosition(212.f, height_dialog - 50.f);
		window.draw(text);

		window.draw(textBox);
		window.draw(user);

		window.display();

	}
}

// This function saves the recording just created to the user provided name
void Save()
{
	int width_dialog = 200, height_dialog = 200;
	std::string word; // This is what the user types

	RenderWindow window(VideoMode(width_dialog, height_dialog), 
						"Save", Style::Default);

	// Creates Save Button
	RectangleShape rectangle(Vector2f(100.f, 30.f));
	rectangle.setPosition(50, 155);
	rectangle.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectSave(50, 155, 100, 30);

	// Creates the text box
	RectangleShape textBox(Vector2f(150.f, 30.f));
	textBox.setPosition(24, 70);
	textBox.setFillColor(Color::White);// Color Light Grey

	// This loads the font
	Font MyFont;
	if (!MyFont.loadFromFile
	("lucidabrightitalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 20); // This creates a Text object
	Text user("", MyFont, 15); // This draws what the user types
	user.setColor(Color::Black);

	while (window.isOpen())
	{
		Event evnt;

		// This loop runs everytime the user does something
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			// This closes the window if the user clicks the close button
			case Event::Closed:
				window.close();
				break;

			// This makes changes to what the user views as they type
			case Event::TextEntered:
			{
				word += evnt.text.unicode;
				user.setString(word);
				user.setPosition(25, 73);
			}
				break;
				 
			// This saves the file when the user clickes save
			case Event::MouseButtonPressed:
				if (rectSave.contains(Mouse::getPosition(window)))
				{
					word += ".txt";
					std::ifstream fin("programsaves.txt");
					std::ofstream fout(word);
					std::string line;

					// This copies the programsaves files to the new created
					// file named by the user
					while (std::getline(fin, line))
					{
						fout << line << std::endl;
					}

					window.close();
				}
				break;
			}
		}
		window.clear();

		// This shows the text
		text.setColor(Color::White);
		text.setString("Filename:");
		text.setPosition(10, 30);
		window.draw(text);

		// This displays the Save Button
		text.setColor(Color::Black);
		window.draw(rectangle);
		text.setString("Save");
		text.setPosition(76, 155);
		window.draw(text);

		window.draw(textBox);
		window.draw(user);

		window.display();

	}
}


int main()
{
	// These are the variables that I will base my sizes on
	int height = 400, width = 810;
	bool selected = false, onceRecorded = false;
	std::ofstream newmusic;

	std::string key_on_computer[] = {"A", "S", "D", "F", "G", "H", "J", "K",
									 "Z", "X", "V", "B", "N"};



	// This creates the window on which the program will be viewed
	RenderWindow window(VideoMode(width, height), "Piano", Style::Default);
	


	// White Keys
	RectangleShape rectangle1(Vector2f((width - 10) / 8.f, height - 65.f));

	// Black Keys
	RectangleShape rectangle2(Vector2f((width - 10) / 16.f - 5, (height / 2.f)
										- 35));



	// Creates Record Button and dot
	RectangleShape rectangle3(Vector2f(100.f, 30.f));
	rectangle3.setPosition(100, 355);
	rectangle3.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle3.setOutlineThickness(5);
	rectangle3.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectRecord(100, 355, 100, 30);

	CircleShape recordDot(10, 100);
	recordDot.setFillColor(Color::Black);
	recordDot.setPosition(65, 362);

	// Creates Play Button
	RectangleShape rectangle4(Vector2f(100.f, 30.f));
	rectangle4.setPosition(350, 355);
	rectangle4.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle4.setOutlineThickness(5);
	rectangle4.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectPlay(350, 355, 100, 30);



	// Creates Save Button
	RectangleShape rectangle5(Vector2f(100.f, 30.f));
	rectangle5.setPosition(600, 355);
	rectangle5.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle5.setOutlineThickness(5);
	rectangle5.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectSave(600, 355, 100, 30);



	// This helps load the sounds to the corresponding buffers named as keys
	SoundBuffer A, Z, S, X, D, F, V, G, B, H, N, J, K;
	if (!A.loadFromFile("1 C3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!Z.loadFromFile("2 C3 Sharp D3 Flat.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!S.loadFromFile("3 D3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!X.loadFromFile("4 D3 Sharp E3 Flat.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!D.loadFromFile("5 E3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!F.loadFromFile("6 F3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!V.loadFromFile("7 F3 Sharp G3 Flat.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!G.loadFromFile("8 G3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!B.loadFromFile("9 G3 Sharp A3 Flat.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!H.loadFromFile("10 A3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!N.loadFromFile("11 A3 Sharp B3 Flat.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!J.loadFromFile("12 B3.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}
	if (!K.loadFromFile("13 C4.wav"))
	{
		std::cout << "ERROR: Loading Sound Effect" << std::endl;
	}




	// This matches each sound with its corresponding buffers
	Sound c3, d3b, d3, e3b, e3, f3, g3b, g3, a3b, a3, b3b, b3, c4;
	c3.setBuffer(A);
	d3b.setBuffer(Z);
	d3.setBuffer(S);
	e3b.setBuffer(X);
	e3.setBuffer(D);
	f3.setBuffer(F);
	g3b.setBuffer(V);
	g3.setBuffer(G);
	a3b.setBuffer(B);
	a3.setBuffer(H);
	b3b.setBuffer(N);
	b3.setBuffer(J);
	c4.setBuffer(K);



	// This loads the font
	Font MyFont;
	if (!MyFont.loadFromFile
	   ("lucidabrightitalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 30); // This creates a Text object


	// This keeps track of the time
	Clock clock;

	// This main loop runs while the window is open
	while (window.isOpen())
	{
		Event evnt;
		
		// This loop runs everytime the user does something
		while (window.pollEvent(evnt))
		{


			// The switch helps the program do different tasks based on 
			// different user actions.
			switch (evnt.type)
			{


			// This closes the window if the user clicks the close button
			case Event::Closed:
				window.close();
				break;



			// This plays the sound corresponding to the computer key pressed
			// everytime a key is pressed.
			// This can play multiple sounds at the same time
			case Event::TextEntered:
				if(evnt.KeyPressed)
				{
					if (selected)
					{
						Time next = clock.getElapsedTime();
						newmusic << next.asSeconds() << " " 
								 << evnt.text.unicode << std::endl;
					}
					while (Keyboard::isKeyPressed(Keyboard::A)) // c3
					{
						c3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::Z)) // c3# or d3b
					{
						d3b.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::S)) // d3
					{
						d3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::X)) // d3# or e3b
					{
						e3b.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::D)) // e3
					{
						e3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::F)) // f3
					{
						f3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::V)) // f3# or g3b
					{
						g3b.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::G)) // g3
					{
						g3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::B)) // g3# or a3b
					{
						a3b.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::H)) // a3
					{
						a3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::N)) // a3# or b3b
					{
						b3b.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::J)) // b3
					{
						b3.play();
					}
					while (Keyboard::isKeyPressed(Keyboard::K)) // c4
					{
						c4.play();
					}
				}
				break;



			// This checks which of the three Buttons is Pressed
			case Event::MouseButtonPressed:

				// This case runs only if the Left Mouse button is pressed
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					// This checks if the record button is pressed
					if (rectRecord.contains(Mouse::getPosition(window)))
					{
						// This switches the state every time Record 
						// is clicked
						selected = !selected;
							
							// The changes when program is recording
							if (selected)
							{
								remove("programsaves.txt");
								rectangle3.setFillColor(Color(96, 96, 96));
								recordDot.setFillColor(Color::Red);
								newmusic.open("programsaves.txt",
											  std::ofstream::out |
											  std::ofstream::trunc);
								clock.restart();
								newmusic << clock.getElapsedTime().asSeconds()
										 << " " << 113 << std::endl;
							}

							// The changes when program is not recording
							else
							{
								rectangle3.setFillColor(Color(192, 192, 192));
								recordDot.setFillColor(Color::Black);
								newmusic << clock.getElapsedTime().asSeconds()
										 << " Stopped"
										 << std::endl;
							}
					}

					// This checks if the play button is pressed
					// These changes occur if it is
					if (rectPlay.contains(Mouse::getPosition(window)))
					{
						rectangle4.setFillColor(Color(96, 96, 96));
						Play();
						rectangle4.setFillColor(Color(192, 192, 192));
					}

					// This checks if the save button is pressed
					// These changes occur if it is
					if (rectSave.contains(Mouse::getPosition(window)))
					{
						rectangle5.setFillColor(Color(96, 96, 96));
						if (SoundBufferRecorder::SoundRecorder::isAvailable())
						{
							Save();
						}
						rectangle5.setFillColor(Color(192, 192, 192));
					}
				}
				break;
			}
		}
		window.clear();
		
		// This draws the white keys
		rectangle1.setOutlineThickness(5);
		rectangle1.setOutlineColor(Color(105,105,105)); // Color Grey
		for (float i = 5.0; i < 800.0; i += 100.0)
		{
			rectangle1.setPosition(i, 0.f);
			window.draw(rectangle1);
		}

		// This draws the black keys
		rectangle2.setOutlineThickness(5);
		rectangle2.setOutlineColor(Color(105, 105, 105)); // Color Grey
		rectangle2.setFillColor(Color::Black);
		for (float i = 80.0, run = 1; i < 600.0; i += 100.0, run++)
		{
			if (run != 3) // This skips the third black key position
			{
				rectangle2.setPosition(i, 0.f);
				window.draw(rectangle2);
			}
		}

		// These views the Buttons on the Application
		text.setColor(Color::Black);
		text.setCharacterSize(20);

		// Record Button
		window.draw(rectangle3);
		text.setString("Record");
		text.setPosition(115, 357.5);
		window.draw(text);

		// Play Button
		window.draw(rectangle4);
		text.setString("Play");
		text.setPosition(377, 357.5);
		window.draw(text);

		// Save Button
		window.draw(rectangle5);
		text.setString("Save");
		text.setPosition(627, 357.5);
		window.draw(text);

		// This creates the keyboard key labels
		int run = 0;
		text.setCharacterSize(30);

		// This draws the text on the piano
		for (float i = 39.0; run < 13; i += 100.0, run++)
		{
			text.setString(key_on_computer[run]); // Sets to computer keys
			if (run < 8) // Runs for white keys correspondants
			{
				text.setPosition(i, 285.0);
			}
			else // Runs for black keys correspondants
			{
				if (run == 8) //This switches the position back for black keys
				{
					i = 91.5;
					text.setColor(Color::White);
				}
				if (run == 10) // This skips a position
				{
					i += 100.0;
				}
				text.setPosition(i, 120.0);
			}
			window.draw(text);
		}
		window.draw(recordDot);
		window.display();
	}
	return 0;
}