/**
 * @author Noam Karasso
 */

package gui;

import java.awt.*;
import java.awt.event.*;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;

import javax.swing.*;

import factory.RaceBuilder;
import game.arenas.Arena;
import game.arenas.exceptions.RacerLimitException;
import game.arenas.exceptions.RacerTypeException;
import game.racers.Racer;
import utilities.EnumContainer.Color;

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
	private static final int INFO_COLUMNS = 5;

	private int windowWidth;
	private int windowHeight;
	
	private JTextField text_length;
	private JTextField text_maxRacers;
	private JTextField text_rName;
	private JTextField text_maxSpeed;
	private JTextField text_acceleration;

	private JComboBox<String> combo_arenas;
	private JComboBox<String> combo_racers;
	private JComboBox<String> combo_colors;

	private boolean raceStarted;
	private boolean arenaBuilt;
	private boolean raceFinished;

	private int maxRacers;
	private int nofRacers;

	
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
		
		arenaBuilt = false;
		raceStarted = false;
		raceFinished = false;

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
		label1.setBounds(10, 20, 100, 10);
		cPanel.add(label1);

		String arenas[] = { "AerialArena", "LandArena", "NavalArena" };
		combo_arenas = new JComboBox<>(arenas);
		combo_arenas.setBounds(10, 40, 100, 20);
		cPanel.add(combo_arenas);

		JLabel label2 = new JLabel("Arena length:");
		label2.setBounds(10, 70, 100, 10);
		cPanel.add(label2);

		text_length = new JTextField("" + DEFAULT_WIDTH);
		text_length.setBounds(10, 90, 50, 20);
		cPanel.add(text_length);

		JLabel label3 = new JLabel("Max racers number:");
		label3.setBounds(10, 120, 150, 10);
		cPanel.add(label3);

		text_maxRacers = new JTextField("" + maxRacers);
		text_maxRacers.setBounds(10, 140, 50, 20);
		cPanel.add(text_maxRacers);

		JButton button = new JButton("Build arena");
		button.addActionListener(this);
		button.setBounds(10, 170, 100, 30);
		cPanel.add(button);

		JSeparator sep = new JSeparator(SwingConstants.HORIZONTAL);
		sep.setBounds(0, 210, 150, 10);
		cPanel.add(sep, BorderLayout.CENTER);

		// ADD RACER PART
		JLabel label4 = new JLabel("Choose racer:");
		label4.setBounds(10, 230, 100, 10);
		cPanel.add(label4);

		String racers[] = { "Airplane", "Helicopter", "Bicycle", "Car", "Horse", "RowBoat", "SpeedBoat" };
		combo_racers = new JComboBox<>(racers);
		combo_racers.setBounds(10, 250, 100, 20);
		cPanel.add(combo_racers);

		JLabel label5 = new JLabel("Choose color:");
		label5.setBounds(10, 280, 100, 10);
		cPanel.add(label5);

		String colors[] = { "Black", "Blue", "Green", "Red", "Yellow" };
		combo_colors = new JComboBox<>(colors);
		combo_colors.setBounds(10, 300, 100, 20);
		cPanel.add(combo_colors);

		JLabel label6 = new JLabel("Racer name:");
		label6.setBounds(10, 330, 100, 10);
		cPanel.add(label6);

		text_rName = new JTextField();
		text_rName.setBounds(10, 350, 50, 20);
		cPanel.add(text_rName);

		JLabel label7 = new JLabel("Max speed:");
		label7.setBounds(10, 380, 100, 10);
		cPanel.add(label7);

		text_maxSpeed = new JTextField();
		text_maxSpeed.setBounds(10, 400, 50, 20);
		cPanel.add(text_maxSpeed);

		JLabel label8 = new JLabel("Acceleration:");
		label8.setBounds(10, 430, 100, 10);
		cPanel.add(label8);

		text_acceleration = new JTextField();
		text_acceleration.setBounds(10, 450, 50, 20);
		cPanel.add(text_acceleration);

		JButton button1 = new JButton("Add racer");
		button1.addActionListener(this);
		button1.setBounds(10, 480, 100, 30);
		cPanel.add(button1);

		JSeparator sep2 = new JSeparator(SwingConstants.HORIZONTAL);
		sep2.setBounds(0, 530, 150, 10);
		cPanel.add(sep2, BorderLayout.SOUTH);

		// ADD BOTTOM PART
		JButton button2 = new JButton("Start race");
		button2.addActionListener(this);
		button2.setBounds(10, 550, 100, 30);
		cPanel.add(button2);

		JButton button3 = new JButton("Show info");
		button3.addActionListener(this);
		button3.setBounds(10, 600, 100, 30);
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
		
			for (Racer r: arena.getActiveRacers()) {
				new Thread(r).start();
			}
		
	}
	
	/**
	 *This method is called when the user clicks the "Show info" button
	 *It checks if the arena has been built and racers have been added, if not, it displays an error message and returns
	 *If all requirements are met, it creates a table that displays information about each racer, such as name, current speed
	 *maximum speed, current location, and whether or not the racer has finished the race
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
			i++;
		}

		for (Racer racer : arena.getActiveRacers()) {
			data[i][0] = racer.getName();
			data[i][1] = "" + racer.getCurrentSpeed();
			data[i][2] = "" + racer.getMaxSpeed();
			data[i][3] = "" + racer.getCurrentLocation().getX();
			data[i][4] = "No";
			i++;
		}
		
		JFrame infoF = new JFrame("Racers information");
		ImageIcon img = new ImageIcon(new ImageIcon("icons/java.png").getImage().getScaledInstance(ICON_SIZE, ICON_SIZE, Image.SCALE_DEFAULT));
		infoF.setIconImage(img.getImage());
		infoF.pack();
		
		// adjust it according to the user's screen resolution
		int infoHeight = Math.max((maxRacers*20), 220);
		infoF.setBounds(dimension.width / 2 - 250, dimension.height / 2 - infoHeight/2, 500, infoHeight);
		
		String[] columnNames = { "Racer name", "Current speed", "Max speed", "Current X location", "Finished" };
		JTable table = new JTable(data,columnNames);
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
		switch (combo_colors.getSelectedItem().toString()) {
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
				switch (combo_arenas.getSelectedItem().toString()) {
				case "AerialArena":
					arena = builder.buildArena("game.arenas.air.AerialArena", length, maxRacers);
					break;
				case "LandArena":
					arena = builder.buildArena("game.arenas.land.LandArena", length, maxRacers);
					break;
				case "NavalArena":
					arena = builder.buildArena("game.arenas.naval.NavalArena", length, maxRacers);
				}
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
	 
}
