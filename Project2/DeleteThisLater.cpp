/*
#include "stdafx.h"
using namespace sf;
namespace fs = std::experimental::filesystem;

void Record()
{

}


void Play()
{
	int width_dialog = 300, height_dialog = 600;
	std::string word;

	RenderWindow window(VideoMode(width_dialog, height_dialog),
		"Play", Style::Default);

	// Creates Record Button
	RectangleShape rectangle(Vector2f(100.f, 30.f));
	rectangle.setPosition(190.f, height_dialog - 50.f);
	rectangle.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectSave(190, height_dialog - 50, 100, 30);

	RectangleShape textBox(Vector2f(175.f, 30.f));
	textBox.setPosition(5.f, height_dialog - 50.f);
	textBox.setFillColor(Color::White);// Color Light Grey

	// This loads the font I want
	Font MyFont;
	if (!MyFont.loadFromFile
	("C:/Program Files/Java/jre-10.0.1/lib/fonts/LucidaBrightItalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 20); // This creates a Text object
	Text user("", MyFont, 15);
	user.setColor(Color::Black);

	std::vector<std::string> FILES;
	std::vector<std::string> file_names;

	std::string path("C:\\Users\\mousu\\C++\\Project2\\Project2");
	for (auto& p : fs::recursive_directory_iterator(path))
	{
		fs::path path = p.path();
		std::string path_string = path.string();
		for (auto &c : path_string)
			c = tolower(c);
		std::string extension_string = p.path().extension().string();
		for (auto &c : extension_string)
			c = tolower(c);
		//std::string path_string = p.path.string();
		/*std::transform(path_string.begin(), path_string.end(), lower_path_string, ::toupper);
		/*std::string extension = std::to_string(p.path().extension());
if (extension_string == ".wav")
{
	FILES.push_back(path_string);
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
				word += evnt.text.unicode; // 
				user.setString(word);
				user.setPosition(10.f, height_dialog - 47.f);
			}
			break;

			case Event::MouseButtonPressed:
				if (rectSave.contains(Mouse::getPosition(window)))
				{
					bool is_file_error = true;
					//word += ".wav";

					for (int i = 0; i < FILES.size(); i++)
					{
						if (file_names[i] == word)
							is_file_error = false;
					}
					if (is_file_error)
					{
						std::cout << "File does not exist, please re-type";
						word = "";
						user.setString(word);
						user.setPosition(10.f, height_dialog - 47.f);
					}
					else
					{
						SoundBuffer playThis;
						if (!playThis.loadFromFile(word))
						{
							std::cout << "ERROR: Loading Sound Effect" << std::endl;
						}
						Sound sound;
						sound.setBuffer(playThis);
						sound.play();
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

		text.setCharacterSize(15);
		for (int i = 0, x = 60; i < file_names.size(); i++)
		{
			text.setString(file_names[i]);
			text.setPosition(5, x);
			window.draw(text);
			x += 20;
		}

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

void Save(SoundBuffer& recording)
{
	int width_dialog = 200, height_dialog = 200;
	std::string word;

	RenderWindow window(VideoMode(width_dialog, height_dialog),
		"Save", Style::Default);

	// Creates Record Button
	RectangleShape rectangle(Vector2f(100.f, 30.f));
	rectangle.setPosition(50, 155);
	rectangle.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rectSave(50, 155, 100, 30);

	RectangleShape textBox(Vector2f(150.f, 30.f));
	textBox.setPosition(24, 70);
	textBox.setFillColor(Color::White);// Color Light Grey

	// This loads the font I want
	Font MyFont;
	if (!MyFont.loadFromFile
	("C:/Program Files/Java/jre-10.0.1/lib/fonts/LucidaBrightItalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 20); // This creates a Text object
	Text user("", MyFont, 15);
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

			case Event::TextEntered:
			{
				word += evnt.text.unicode; // 
				user.setString(word);
				user.setPosition(25, 73);
			}
			break;

			case Event::MouseButtonPressed:
				if (rectSave.contains(Mouse::getPosition(window)))
				{
					word += ".wav";
					recording.saveToFile(word);
					window.close();
				}
				break;
			}
		}
		window.clear();

		text.setColor(Color::White);
		text.setString("Filename:");
		text.setPosition(10, 30);
		window.draw(text);

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
	bool selected = false;
	std::string key_on_computer[] = { "A", "S", "D", "F", "G", "H", "J", "K",
									 "Z", "X", "V", "B", "N" };



	// This creates the window on which the program will be viewed
	RenderWindow window(VideoMode(width, height), "Piano", Style::Default);



	// White Keys
	RectangleShape rectangle1(Vector2f((width - 10) / 8.f, height - 65.f));

	// Black Keys
	RectangleShape rectangle2(Vector2f((width - 10) / 16.f - 5, (height / 2.f)
		- 35));



	// Creates Record Button
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



	// Record some audio data
	SoundBuffer copy;
	if (!sf::SoundBufferRecorder::isAvailable())
		std::cout << "get a mic" << std::endl;

	sf::SoundBufferRecorder recorder;
	sf::SoundBuffer buffer;
	sf::Sound sound;



	// This loads the font I want
	Font MyFont;
	if (!MyFont.loadFromFile
	("C:/Program Files/Java/jre-10.0.1/lib/fonts/LucidaBrightItalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 30); // This creates a Text object



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
				if (evnt.KeyPressed)
				{
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
						selected = !selected;

						if (selected)
						{
							rectangle3.setFillColor(Color(96, 96, 96));
							recordDot.setFillColor(Color::Red);
						}
						else
						{
							rectangle3.setFillColor(Color(192, 192, 192));
							recordDot.setFillColor(Color::Black);

						}


					}

					// This checks if the play button is pressed
					if (rectPlay.contains(Mouse::getPosition(window)))
					{
						rectangle4.setFillColor(Color(96, 96, 96));
						Play();
						rectangle4.setFillColor(Color(192, 192, 192));
					}

					// This checks if the save button is pressed
					if (rectSave.contains(Mouse::getPosition(window)))
					{
						rectangle5.setFillColor(Color(96, 96, 96));
						if (SoundBufferRecorder::SoundRecorder::isAvailable())
						{
							Save(copy);
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
		rectangle1.setOutlineColor(Color(105, 105, 105)); // Color Grey
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
				if (run == 8) // This switches the position back for black keys
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

/*

// Sound Recorder
						if (SoundBufferRecorder::SoundRecorder::isAvailable())
						{
							std::vector<std::string> availableDevices = SoundRecorder::getAvailableDevices();
							std::string inputDevice = availableDevices[0];
							recorder.setDevice(inputDevice);
							}

boolean ReplayJustRecorded()
{
	int width_dialog = 500, height_dialog = 200;
	std::string given_name;

	RenderWindow window(VideoMode(width_dialog, height_dialog),
		"Play Recording", Style::Default);

	// Creates Record Button
	RectangleShape rectangle1(Vector2f(100.f, 30.f));
	rectangle1.setPosition(100, 100);
	rectangle1.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle1.setOutlineThickness(5);
	rectangle1.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rect1(100, 100, 100, 30);

	// Creates Record Button
	RectangleShape rectangle2(Vector2f(100.f, 30.f));
	rectangle2.setPosition(300, 100);
	rectangle2.setFillColor(Color(192, 192, 192));// Color Light Grey
	rectangle2.setOutlineThickness(5);
	rectangle2.setOutlineColor(Color(105, 105, 105)); // Color Grey
	IntRect rect2(300, 100, 100, 30);

	// This loads the font I want
	Font MyFont;
	if (!MyFont.loadFromFile
	("C:/Program Files/Java/jre-10.0.1/lib/fonts/LucidaBrightItalic.ttf"))
	{
		std::cout << "ERROR: Loading Font" << std::endl;
	}
	Text text("", MyFont, 30); // This creates a Text object

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

			case Event::MouseButtonPressed:
				if (rect1.contains(Mouse::getPosition(window)))
				{
					window.close();
					return true;
				}
				else if (rect2.contains(Mouse::getPosition(window)))
				{
					window.close();
					return false;
				}
				break;
			}
		}
		window.clear();


		window.draw(rectangle1);

		window.draw(rectangle2);

		// These views the Buttons on the Application
		text.setColor(Color::White);
		text.setCharacterSize(20);

		text.setString("Do you want to replay your last recording?");
		text.setPosition(60, 30);
		window.draw(text);

		// Yes Button
		text.setColor(Color::Black);

		window.draw(rectangle1);
		text.setString("Yes");
		text.setPosition(333, 100);
		window.draw(text);

		// No Button
		window.draw(rectangle1);
		text.setString("No");
		text.setPosition(137, 100);
		window.draw(text);

		window.display();

	}
}
*/