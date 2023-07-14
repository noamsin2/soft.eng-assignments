/**
 * @author Noam Karasso
 */

package gui;

import java.awt.*;
import java.awt.event.*;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import javax.swing.*;
import factory.ArenaFactory;
import factory.CarRaceBuilder;
import factory.RaceBuilder;
import factory.RaceEngineer;
import game.arenas.Arena;
import game.arenas.exceptions.RacerLimitException;
import game.arenas.exceptions.RacerTypeException;
import game.race.Race;
import game.racers.Racer;
import utilities.EnumContainer.Color;
import factory.VehicleWorkshop;

/**
 *The raceFrame class extends JFrame and implements ActionListener to create a GUI for a racing game
 *It contains the GUI components and functions to control the game such as building the arena, adding racers,
 *and starting the race
 */
class raceFrame extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;
	private static final int DEFAULT_WIDTH = 1000;
	private static final int EXTRA_WIDTH = 80;
	private static final int CONTROL_PANEL_SIZE = 150;
	private static final int DEFAULT_HEIGHT = 700;
	private static final int DEFAULT_RACERS = 8;
	private static final int ICON_SIZE = 32;
	private static final int RACER_ICON_SIZE = 65;
	private static final int MAX_RACERS = 20;
	private static final int MIN_RACERS = 1;
	private static final int MAX_LENGTH = 3000;
	private static final int MIN_LENGTH = 100;
	private static final int INFO_COLUMNS = 6;

	private int windowWidth;
	private int windowHeight;
	
	private JTextField text_length;
	private JTextField text_maxRacers;
	private JTextField text_rName;
	private JTextField text_maxSpeed;
	private JTextField text_acceleration;
	private JTextField text_nofRacers;
	
	private JComboBox<String> combo_arenas;
	private JComboBox<String> combo_racers;
	private JComboBox<String> combo_colors;

	private boolean raceStarted;
	private boolean arenaBuilt;
	private boolean raceFinished;

	private int maxRacers;
	private int nofRacers;
	
	private ArenaFactory AF;
	private VehicleWorkshop vehicleWS;
	
	private Dimension dimension;

	private Arena arena = null;
	private static RaceBuilder builder = RaceBuilder.getInstance();;
	private ArrayList<Racer> racers = null;
	private JLabel bgPic;
	

	/**
	 * The constructor for the `raceFrame` class. It initializes the frame and sets the default values for the 
	 * components in the frame
	 * @param title the title of the frame
	 */
	public raceFrame(String title) {
		super(title);
		dimension = Toolkit.getDefaultToolkit().getScreenSize();
		
		maxRacers = DEFAULT_RACERS;
		windowWidth = DEFAULT_WIDTH;
		windowHeight = DEFAULT_HEIGHT;
		nofRacers = 0;
		//racers = new ArrayList<Racer>();
		arenaBuilt = false;
		raceStarted = false;
		raceFinished = false;
		AF = new ArenaFactory();
		vehicleWS = new VehicleWorkshop();
		ImageIcon img = new ImageIcon(new ImageIcon("icons/java.png").getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_DEFAULT));
		setIconImage(img.getImage());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		makeFrame();

		setVisible(true);
	}


	/**
	 * The `makeFrame` function creates the components of the frame and arranges them on the screen
	 */
	private void makeFrame() {
		pack();

		// adjust it according to the user's screen resolution
		
		//windowWidth = Math.min(dimension.width, arenaLength+ 150);
		//windowHeight = Math.min(dimension.height, arenaHeight);
		if(arena != null) {
			windowWidth = (int)arena.getLength() + CONTROL_PANEL_SIZE + EXTRA_WIDTH;
			windowHeight = Math.max(DEFAULT_HEIGHT, arena.getHeight());
		}
		setBounds(dimension.width / 2 - windowWidth / 2, dimension.height / 2 - windowHeight / 2, windowWidth,
				windowHeight);

		JPanel panels = new JPanel();
		panels.setLayout(new BorderLayout());
		
		panels.add(arenaPanel(), BorderLayout.WEST);
		panels.add(new JSeparator(SwingConstants.VERTICAL), BorderLayout.CENTER);
		panels.add(controlPanel(), BorderLayout.EAST);

		this.setContentPane(panels);
		
	}

	/**
	 * The `arenaPanel` function creates the panel that displays the arena
	 * @return the panel that displays the arena
	 */
	private JPanel arenaPanel() {
		JPanel arenaPanel = new JPanel();
		arenaPanel.setLayout(new BorderLayout());
		
		arenaPanel.setPreferredSize(new Dimension(windowWidth - CONTROL_PANEL_SIZE, windowHeight));

		if (arena != null) {
			ImageIcon img = arena.getIcon();
			bgPic = new JLabel(img);
			//bgPic.setSize(arenaLength, arenaHeight);
			arenaPanel.add(bgPic);
		}
		return arenaPanel;
	}

	
	
	/**
	 *Creates the control panel of the race frame. The control panel contains the
	 *options to build the arena, add racers, and start the race
	 *@return a JPanel containing the control options
	 */
	private JPanel controlPanel() {

		JPanel cPanel = new JPanel();

		cPanel.setLayout(null);
		cPanel.setPreferredSize(new Dimension(CONTROL_PANEL_SIZE-17, windowHeight));

		// ADD ARENA PART
		JLabel label1 = new JLabel("Choose arena:");
		label1.setBounds(10, 10, 100, 10);
		cPanel.add(label1);

		String arenas[] = { "Air", "Land", "Naval" };
		combo_arenas = new JComboBox<>(arenas);
		combo_arenas.setBounds(10, 25, 100, 20);
		cPanel.add(combo_arenas);

		JLabel label2 = new JLabel("Arena length:");
		label2.setBounds(10, 50, 100, 10);
		cPanel.add(label2);

		text_length = new JTextField("" + DEFAULT_WIDTH);
		text_length.setBounds(10, 65, 50, 20);
		cPanel.add(text_length);

		JLabel label3 = new JLabel("Max racers number:");
		label3.setBounds(10, 90, 150, 10);
		cPanel.add(label3);

		text_maxRacers = new JTextField("" + maxRacers);
		text_maxRacers.setBounds(10, 105, 50, 20);
		cPanel.add(text_maxRacers);

		JButton button = new JButton("Build arena");
		button.addActionListener(this);
		button.setBounds(10, 130, 100, 30);
		cPanel.add(button);

		JSeparator sep = new JSeparator(SwingConstants.HORIZONTAL);
		sep.setBounds(0, 165, 150, 10);
		cPanel.add(sep, BorderLayout.CENTER);

		// ADD RACER PART
		JLabel label4 = new JLabel("Choose racer:");
		label4.setBounds(10, 180, 100, 10);
		cPanel.add(label4);

		String racers[] = { "Airplane", "Helicopter", "Bicycle", "Car", "Horse", "RowBoat", "SpeedBoat" };
		combo_racers = new JComboBox<>(racers);
		combo_racers.setBounds(10, 195, 100, 20);
		cPanel.add(combo_racers);

		JLabel label5 = new JLabel("Choose color:");
		label5.setBounds(10, 220, 100, 10);
		cPanel.add(label5);

		String colors[] = { "Black", "Blue", "Green", "Red", "Yellow" };
		combo_colors = new JComboBox<>(colors);
		combo_colors.setBounds(10, 235, 100, 20);
		cPanel.add(combo_colors);

		JLabel label6 = new JLabel("Racer name:");
		label6.setBounds(10, 260, 100, 10);
		cPanel.add(label6);

		text_rName = new JTextField();
		text_rName.setBounds(10, 275, 50, 20);
		cPanel.add(text_rName);

		JLabel label7 = new JLabel("Max speed:");
		label7.setBounds(10, 300, 100, 10);
		cPanel.add(label7);

		text_maxSpeed = new JTextField();
		text_maxSpeed.setBounds(10, 315, 50, 20);
		cPanel.add(text_maxSpeed);

		JLabel label8 = new JLabel("Acceleration:");
		label8.setBounds(10, 340, 100, 10);
		cPanel.add(label8);

		text_acceleration = new JTextField();
		text_acceleration.setBounds(10, 355, 50, 20);
		cPanel.add(text_acceleration);

		JButton button1 = new JButton("Add racer");
		button1.addActionListener(this);
		button1.setBounds(10, 380, 110, 30);
		cPanel.add(button1);
		
		JButton button4 = new JButton("Copy racers");
		button4.addActionListener(this);
		button4.setBounds(10, 415, 110, 30);
		cPanel.add(button4);

		JSeparator sep2 = new JSeparator(SwingConstants.HORIZONTAL);
		sep2.setBounds(0, 450, 150, 10);
		cPanel.add(sep2, BorderLayout.SOUTH);
		// ADD BUILDER PART
		
		JLabel label9 = new JLabel("Instant car race");
		label9.setBounds(5, 460, 130, 10);
		label9.setFont(new Font("Arial", Font.BOLD, 15)); // Set the font, style, and size
		label9.setForeground(java.awt.Color.BLUE);
		cPanel.add(label9);

		JLabel label10 = new JLabel("Num of racers:");
		label10.setBounds(10, 485, 100, 10);
		cPanel.add(label10);
		
		text_nofRacers = new JTextField();
		text_nofRacers.setBounds(10, 500, 50, 20);
		cPanel.add(text_nofRacers);
		
		JButton button5 = new JButton("Build car race");
		button5.addActionListener(this);
		button5.setBounds(10, 525, 120, 30);
		cPanel.add(button5);
		
		JSeparator sep3 = new JSeparator(SwingConstants.HORIZONTAL);
		sep3.setBounds(0, 570, 150, 10);
		cPanel.add(sep3, BorderLayout.SOUTH);
		
		// ADD BOTTOM PART
		JButton button2 = new JButton("Start race");
		button2.addActionListener(this);
		button2.setBounds(10, 585, 100, 30);
		cPanel.add(button2);

		JButton button3 = new JButton("Show info");
		button3.addActionListener(this);
		button3.setBounds(10, 625, 100, 30);
		cPanel.add(button3);

		return cPanel;
	}

	/**
	 *This method is called when the user clicks one of the buttons in the control panel
	 *It receives an ActionEvent as a parameter that contains information about the button that was clicked
	 *It uses a switch statement to determine which button was clicked and then calls the relevant method
	 *@param e ActionEvent object containing information about the button that was clicked
	 */
	public void actionPerformed(ActionEvent e) {
		switch (e.getActionCommand()) {

		case "Build arena":
			buildArena();
			break;

		case "Add racer":
			addRacer();
			break;

		case "Start race":
			startRace();
			break;

		case "Show info":
			showInfo();
			break;
			
		case "Copy racers":
			copyRacers();
			break;
			
		case "Build car race":
			buildCarRace();
		}
	}
	
	/**
	 * Builds a car race based on the user input and constructs the race with 'Land' arena and default cars
	 * It validates the input, checks if the race has already started, and handles exceptions during the process
	 */
	private void buildCarRace() {
		int nof_racers;
		try {
			nof_racers = Integer.parseInt(text_nofRacers.getText());
		} catch (NumberFormatException | NullPointerException ex) {
			System.out.println("Given String is not parsable to int");
			JOptionPane.showMessageDialog(this, "nof_racers must be a number!");
			return;
		}
		;
		if (raceStarted == true) {
			JOptionPane.showMessageDialog(this, "Race already started!");
			return;
		} else if (nof_racers > MAX_RACERS || nof_racers < MIN_RACERS) {
			JOptionPane.showMessageDialog(this, "Invalid input values! Please try again.");
			return;
		}
		//try building arena
			try {
				CarRaceBuilder crBuilder = new CarRaceBuilder();
				RaceEngineer raceE = new RaceEngineer(crBuilder);
				raceE.constructRace(nof_racers);
				Race race = raceE.getRace();
				arena = race.getArena();
				makeFrame();
				nofRacers = 0;
				racers = new ArrayList<Racer>();
				//try adding racers to arena
				try {
				for(int i =0;i<nof_racers;i++) {
					Racer tempRacer = race.getRacers().get(i);
					arena.addRacer(tempRacer);
					nofRacers++;
					racers.add(tempRacer);
					addRacerIcon();
				}
				}
				catch (RacerLimitException ex) {
					System.out.println("[Error] " + ex.getMessage());
					JOptionPane.showMessageDialog(this, ex.getMessage());
				} catch (RacerTypeException ex) {
					System.out.println("[Error] " + ex.getMessage());
					JOptionPane.showMessageDialog(this, ex.getMessage());
				}
				arenaBuilt = true;
				raceFinished = false;
			} catch (ClassNotFoundException | NoSuchMethodException | SecurityException | InstantiationException
					| IllegalAccessException | IllegalArgumentException | InvocationTargetException e1) {
				System.out.println("Unable to build arena!");
			}		
	}
	
	/**
	 *This method is called when the user clicks the "Start race" button
	 *It checks if the arena has been built and racers have been added, if not, it displays an error message
	 *If the race has already started or finished, it also displays an error message
	 *If all requirements are met, it starts the race
	 *a new thread is started for each active racer as well as for updating the racers icons on the screen
	 */
	private void startRace() {
		if (!arenaBuilt) {
			JOptionPane.showMessageDialog(this, "Please build an arena first and add racers!");
			return;
		}
		else if (nofRacers == 0) {
			JOptionPane.showMessageDialog(this, "Please first add racers!");
			return;
		}
		else if(raceStarted) {
			JOptionPane.showMessageDialog(this, "A race is already taking place!");
			return;
		}
		else if(raceFinished) {
			JOptionPane.showMessageDialog(this, "Please build a new arena and add racers first!");
			return;
		}
		raceStarted = true;
		arena.setStartTime(System.currentTimeMillis());
		
		/**
		 * Thread that updates racers on the gui according to their location until the race is finished
		 */
		(new Thread() {
				public void run() {
					while (arena.hasActiveRacers()) {
						updateRacers();
						try {
							Thread.sleep(30);
						} catch (InterruptedException ex) {
							ex.printStackTrace();
						}
					}
					raceFinished = true;
					raceStarted = false;
				}
			}).start();
		
			/**
			 * a Daemon thread to sort racers by distance
			 * Note: uses thread-safe functions to sort
			 */
			Thread sortThread = new Thread(new Runnable() {
	            @Override
	            public void run() {
	            	// Sort the racers by placement
	            	while(arena.hasActiveRacers()) {
	            		arena.sortActiveRacers();
	            		arena.sortDisabledRacers();
	            	}
	            }
	        });
	        sortThread.setDaemon(true);
	        
			for (Racer r: racers) {
				new Thread(r).start();
			}
			
			sortThread.start();
	}
	
	/**
	 *This method is called when the user clicks the "Show info" button
	 *It checks if the arena has been built and racers have been added, if not, it displays an error message and returns
	 *If all requirements are met, it creates a table that displays information about each racer, such as name, current speed
	 *maximum speed, current location, whether or not the racer has finished the race or failed the race, and placement
	 */
	private void showInfo() {
		if (!arenaBuilt) {
			JOptionPane.showMessageDialog(this, "Please build an arena first and add racers!");
			return;
		}
		else if (nofRacers == 0) {
			JOptionPane.showMessageDialog(this, "Please first add racers!");
			return;
		}
		String[][]data = new String[maxRacers][INFO_COLUMNS];
		int i = 0;
		
			for (Racer racer : arena.getCompletedRacers()) {
				data[i][0] = racer.getName();
				data[i][1] = "" + racer.getCurrentSpeed();
				data[i][2] = "" + racer.getMaxSpeed();
				data[i][3] = "" + racer.getCurrentLocation().getX();
				data[i][4] = "Yes";
				data[i][5] = "" + (i+1);
				i++;
			}

		synchronized(arena.getActiveRacers()) {
			for (Racer racer : arena.getActiveRacers()) {
				data[i][0] = racer.getName();
				data[i][1] = "" + racer.getCurrentSpeed();
				data[i][2] = "" + racer.getMaxSpeed();
				data[i][3] = "" + racer.getCurrentLocation().getX();
				data[i][4] = "No";
				i++;
			}
		}
		
		synchronized(arena.getDisabledRacers()) {
			for (Racer racer : arena.getDisabledRacers()) {
				data[i][0] = racer.getName();
				data[i][1] = "" + racer.getCurrentSpeed();
				data[i][2] = "" + racer.getMaxSpeed();
				data[i][3] = "" + racer.getCurrentLocation().getX();
				data[i][4] = "Failed";
				i++;	
			}
		}
		
		JFrame infoF = new JFrame("Racers information");
		ImageIcon img = new ImageIcon(new ImageIcon("icons/java.png").getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_DEFAULT));
		infoF.setIconImage(img.getImage());
		infoF.pack();
		
		// adjust it according to the user's screen resolution
		int infoHeight = Math.max((maxRacers*20), 220);
		infoF.setBounds(dimension.width / 2 - 250, dimension.height / 2 - infoHeight/2, 500, infoHeight);
		String[] columnNames = { "Racer name", "Current speed", "Max speed", "Current X location", "Finished", "Placement"};
		JTable table = new JTable(data, columnNames);
		JScrollPane sp = new JScrollPane(table);
		sp.setBounds(10,10,460,Math.max(155, (int)(maxRacers*17.2)));
		infoF.setLayout(null);
		infoF.add(sp);
		infoF.setVisible(true);
	}
	
	/**
	 *Adds a new racer to the arena.
	 *Checks if the arena is built, the race has not started and has not finished
	 *If the racer name is empty, an error message is displayed
	 *Parses the input strings of maxSpeed and acceleration to double values
	 *If they are not valid numbers, displays an error message
	 *If maxSpeed or acceleration is negative or zero, displays an error message
	 *If the racer limit has been reached, or if the racer type is not supported, displays an error message
	 *Uses the selected color to set the racer's color
	 *Uses the selected racer type to create a new racer and adds it to the arena and to the list of racers
	 *Also creates an image icon of the racer and adds it to the list of racer images
	 */
	private void addRacer() {
		if (arenaBuilt == false) {
			JOptionPane.showMessageDialog(this, "Please build an arena first!");
			return;
		} else if (raceStarted == true) {
			JOptionPane.showMessageDialog(this, "Race already started!");
			return;
		} else if (raceFinished == true) {
			JOptionPane.showMessageDialog(this, "Race already finished!");
			return;
		} else if (text_rName.getText().equals("")) {
			JOptionPane.showMessageDialog(this, "Racer name can't be empty!");
			return;
		}
		double maxSpeed;
		double acceleration;
		try {
			maxSpeed = Double.parseDouble(text_maxSpeed.getText().toString());
			acceleration = Double.parseDouble(text_acceleration.getText().toString());
		} catch (NumberFormatException | NullPointerException ex) {
			System.out.println("Given String is not parsable to double");
			JOptionPane.showMessageDialog(this, "Max speed and acceleration must be numbers!");
			return;
		}
		if(maxSpeed <= 0 || acceleration <= 0) {
			JOptionPane.showMessageDialog(this, "Max speed and acceleration can't be negative or 0 !!!");
			return;
		}
		Color col = null;
		col = colorToEnum(combo_colors.getSelectedItem().toString());
		
		Racer racer = null;
		try {
		switch(combo_racers.getSelectedItem().toString()) {
		case "Airplane":
			racer = builder.buildWheeledRacer("game.racers.air.Airplane", text_rName.getText().toString(), maxSpeed, acceleration, col, 3);
			break;
		case "Helicopter":
			racer = builder.buildRacer("game.racers.air.Helicopter", text_rName.getText().toString(), maxSpeed, acceleration, col);
			break;
		case "Bicycle":
			racer = builder.buildWheeledRacer("game.racers.land.Bicycle", text_rName.getText().toString(), maxSpeed, acceleration, col, 3);
			break;
		case "Car":
			racer = builder.buildWheeledRacer("game.racers.land.Car", text_rName.getText().toString(), maxSpeed, acceleration, col, 4);
			break;
		case "Horse":
			racer = builder.buildRacer("game.racers.land.Horse", text_rName.getText().toString(), maxSpeed, acceleration, col);
			break;
		case "RowBoat":
			racer = builder.buildRacer("game.racers.naval.RowBoat", text_rName.getText().toString(), maxSpeed, acceleration, col);
			break;
		case "SpeedBoat":
			racer = builder.buildRacer("game.racers.naval.SpeedBoat", text_rName.getText().toString(), maxSpeed, acceleration, col);
		}
		}catch(ClassNotFoundException | NoSuchMethodException | SecurityException | InstantiationException
				| IllegalAccessException | IllegalArgumentException | InvocationTargetException ex) {
			ex.printStackTrace();
		}
		try {
			
			arena.addRacer(racer);
			racers.add(racer);
			nofRacers++;
			addRacerIcon();
			
		} catch (RacerLimitException ex) {
			System.out.println("[Error] " + ex.getMessage());
			JOptionPane.showMessageDialog(this, ex.getMessage());
		} catch (RacerTypeException ex) {
			System.out.println("[Error] " + ex.getMessage());
			JOptionPane.showMessageDialog(this, ex.getMessage());
		}
		
	}
	
	/**
	 * Copies a racer by allowing the user to select a racer from the existing racers in the arena and create a copy with a new color and serial number
	 * It validates the race and arena state conditions, opens a dialog window for racer selection and color choice, and performs the necessary operations to copy and add the racer to the arena
	 * If successful, the copied racer is added to the racers list and an icon is displayed
	 */
	private void copyRacers() {
		if (arenaBuilt == false) {
			JOptionPane.showMessageDialog(this, "Please build an arena first!");
			return;
		} else if (raceStarted == true) {
			JOptionPane.showMessageDialog(this, "Race already started!");
			return;
		} else if (raceFinished == true) {
			JOptionPane.showMessageDialog(this, "Race already finished!");
			return;
		}
		JFrame copyF = new JFrame("Racers copying");
		ImageIcon img = new ImageIcon(new ImageIcon("icons/java.png").getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_DEFAULT));
		copyF.setIconImage(img.getImage());
		copyF.pack();
		
		copyF.setBounds(dimension.width / 2 - 350, dimension.height / 2 - 100, 700, 200);
		
		JLabel label = new JLabel("Choose racer by serial number:");
		label.setBounds(10, 10, 100, 10);
		copyF.add(label);

		ArrayList<String>racersList = new ArrayList<String>();
		
		for(Racer r: racers) {
			racersList.add(r.describeRacer());
		}
		String[] racersArray = racersList.toArray(new String[0]);
		JComboBox<String> combo_r = new JComboBox<>(racersArray);
		combo_r.setBounds(10, 30, 600, 20);
		copyF.add(combo_r);

		JLabel label1 = new JLabel("Choose color:");
		label1.setBounds(10, 60, 100, 10);
		copyF.add(label1);

		String colors[] = { "Black", "Blue", "Green", "Red", "Yellow" };
		JComboBox<String> combo_c = new JComboBox<>(colors);
		combo_c.setBounds(10, 80, 100, 20);
		copyF.add(combo_c);
		
		JButton button = new JButton("Copy racer!");
		button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            	Color col = null;
        		col = colorToEnum(combo_c.getSelectedItem().toString());
        		int racerIndex = combo_r.getSelectedIndex();
        		try {
        			//clone the racer
        			Racer copiedRacer = vehicleWS.cloneVehicle(racers.get(racerIndex));
        			//paint the vehicle
        			vehicleWS.paintVehicle(copiedRacer, col);
        			
        			//add racer to arena and show on gui
        			arena.addRacer(copiedRacer);
        			racers.add(copiedRacer);
        			nofRacers++;
        			addRacerIcon();
        		} catch (RacerLimitException ex) {
        			System.out.println("[Error] " + ex.getMessage());
        			JOptionPane.showMessageDialog(null, ex.getMessage());
        		} catch (RacerTypeException ex) {
        			System.out.println("[Error] " + ex.getMessage());
        			JOptionPane.showMessageDialog(null, ex.getMessage());
        		}
            }
        });
		button.setBounds(10, 110, 100, 30);
		copyF.add(button);	
		copyF.setLayout(null);
		copyF.setVisible(true);
	}

	/**
	 *This method is responsible for building an arena according to the user's specifications
	 *It first checks if the race has already started, and if so, displays an error message
	 *It then takes the values entered by the user for the maximum number of racers and the length of the arena, If the values are invalid, it displays an error message
	 *Otherwise, it sets the arena length and maximum racers variables accordingly, and uses the arena builder to create the specified arena
	 *It then rebuilds the frame and initializes the racer and racer image lists
	 */
	private void buildArena() {
		if (raceStarted == true) {
			JOptionPane.showMessageDialog(this, "Please wait for the current race to finish before building an arena!");
			return;
		}
		int mRacers = Integer.parseInt(text_maxRacers.getText());
		int length = Integer.parseInt(text_length.getText());
		if (mRacers < MIN_RACERS || mRacers > MAX_RACERS || length < MIN_LENGTH || length > MAX_LENGTH) {
			JOptionPane.showMessageDialog(this, "Invalid input values! Please try again.");
		} else {
			maxRacers = mRacers;
			try {
				
				arena = AF.createArena(combo_arenas.getSelectedItem().toString(),length,maxRacers);
				makeFrame();
				nofRacers = 0;
				racers = new ArrayList<Racer>();
			
				arenaBuilt = true;
				raceFinished = false;
			} catch (ClassNotFoundException | NoSuchMethodException | SecurityException | InstantiationException
					| IllegalAccessException | IllegalArgumentException | InvocationTargetException e1) {
				System.out.println("Unable to build arena!");
			}
		}
	}
	
	/**
	 *This method updates the location of each racer icon based on their current location
	 *It loops through all the components in the bgPic label and moves the icon
	 *to the current location of the corresponding racer
	 */
	private void updateRacers() {
		int i = 0;
		for (Component c : bgPic.getComponents()) {
				c.setLocation(Math.min((int)racers.get(i).getCurrentLocation().getX(),(int)arena.getLength()),(int)racers.get(i).getCurrentLocation().getY());
				i++;
		}
	}
	
	/**
	 *This method adds a new racer icon to the bgPic label
	 *It creates a new JLabel with the image of the last added racer,
	 *and sets its bounds to the current location of the corresponding racer
	 */
	private void addRacerIcon() {
		JLabel racerIcon = new JLabel(racers.get(nofRacers-1).getIcon());
		racerIcon.setBounds(0,(int)racers.get(nofRacers-1).getCurrentLocation().getY(),RACER_ICON_SIZE,RACER_ICON_SIZE);
		bgPic.add(racerIcon);
		//set frame size to fix icons not showing on the screen
		setSize(windowWidth,windowHeight+nofRacers);
	}
	
	/**
	 *Converts a color string representation to a Color enum value
	 *@param color The color string to convert
	 *@return The Color enum value corresponding to the given color string, or null if no match is found
	 */
	private Color colorToEnum(String color) {
		Color col = null;
		switch (color) {
		case "Black":
			col = Color.BLACK;
			break;
		case "Green":
			col = Color.GREEN;
			break;
		case "Blue":
			col = Color.BLUE;
			break;
		case "Red":
			col = Color.RED;
			break;
		case "Yellow":
			col = Color.YELLOW;
		}
		return col;
	}
	 
}
