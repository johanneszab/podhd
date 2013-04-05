package converter;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.awt.GridBagLayout;
import javax.swing.JCheckBox;
import java.awt.GridBagConstraints;
import javax.swing.JTextField;
import java.awt.Insets;
import javax.swing.JButton;

import javax.swing.ButtonModel;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.File;
import java.io.FileFilter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


import javax.swing.JSeparator;
import java.awt.Color;
import javax.swing.ButtonGroup;
import java.awt.Component;
import javax.swing.Box;
import javax.swing.JComboBox;

public class MainWindow extends JFrame{

	// Constants
	final String patternH5e = "h5e";
	final String patternH5b = "h5b";
	final String patternH5s = "h5s";

	final String patternHbe = "hbe";
	final String patternHbb = "hbb";
	final String patternHbs = "hbs";
	
	final String patternH3e = "h3e";
	final String patternH3b = "h3b";
	final String patternH3s = "h3s";
	
	final String patternH4e = "h4e";
	final String patternH4b = "h4b";
	final String patternH4s = "h4s";
	
	private JPanel contentPane;
	private JPanel hddesktop;
	private JTextField txtFileChooser;
	private JTextField tf300Directory;	
	String choosertitle;
	File dir = null;
	
	// HD Desktop

	JCheckBox chckbxH5e = new JCheckBox("Patch .h5e files");
	JCheckBox chckbxHbe = new JCheckBox("Patch .hbe files");
	JCheckBox chckbxH5b = new JCheckBox("Patch .h5b files");
	JCheckBox chckbxHbb = new JCheckBox("Patch .hbb files");
	JCheckBox chckbxH5s = new JCheckBox("Patch .h5s files");
	JCheckBox chckbxHbs = new JCheckBox("Patch .hbs files");

	JCheckBox chckbxRenameH5e = new JCheckBox("Rename .h5e to .hbe");
	JCheckBox chckbxRenameHbe = new JCheckBox("Rename .hbe to .h5e");
	JCheckBox chckbxRenameH5b = new JCheckBox("Rename .h5b to .hbb");
	JCheckBox chckbxRenameHbb = new JCheckBox("Rename .hbb to .h5b");
	JCheckBox chckbxRenameH5s = new JCheckBox("Rename .h5s to .hbs");
	JCheckBox chckbxRenameHbs = new JCheckBox("Rename .hbs to .h5s");
	
	JCheckBox chckbxBackup = new JCheckBox("Make backup");

	// HD 300

	JCheckBox chckbx300PatchH5e = new JCheckBox("Translate .h5e to .h3e");
	JCheckBox chckbx300PatchH5b = new JCheckBox("Translate .h5b to .h3b");
	JCheckBox chckbx300PatchH5s = new JCheckBox("Translate .h5s to .h3s");

	JCheckBox chckbx400PatchH5e = new JCheckBox("Translate .h5e to .h4e");
	JCheckBox chckbx400PatchH5b = new JCheckBox("Translate .h5b to .h4b");
	JCheckBox chckbx400PatchH5s = new JCheckBox("Translate .h5s to .h4s");
	
	JCheckBox chckbx300Backup = new JCheckBox("Make Backup");

	
	JCheckBox chckbxEditInputs = new JCheckBox("Inputs:");
	String[] sSourceOne = {"Guitar", "Mic"};
	JComboBox<String> cbSourceOne = new JComboBox<String>(sSourceOne);
	String[] sSourceTwo = {"Same", "Guitar", "Mic"};
	JComboBox<String> cbSourceTwo = new JComboBox<String>(sSourceTwo);
	String[] sGuitarIn = {"Auto", "22k", "32k", "70k", "90k", "136k", "230k", "1M", "3,5M" };
	JComboBox<String> cbGuitarIn = new JComboBox<String>(sGuitarIn);
	
	int sourceOne = 0x01;
 	int sourceTwo = 0x00;
 	int guitarIn = 0x00;
	
	List<JCheckBox> lPatchCheckboxes = new ArrayList<JCheckBox>();
	List<JCheckBox> lRenameCheckboxes = new ArrayList<JCheckBox>();
	List<String> lFileExtension = new ArrayList<String>();
	List<String> lFileExtensionReverse = new ArrayList<String>();
	
	List<JCheckBox> lPatchCheckboxes300 = new ArrayList<JCheckBox>();
	List<String> lFileExtension300 = new ArrayList<String>();
	List<String> lFileExtension300Reverse = new ArrayList<String>();
	
	List<JCheckBox> lPatchCheckboxes400 = new ArrayList<JCheckBox>();
	List<String> lFileExtension400 = new ArrayList<String>();
	List<String> lFileExtension400Reverse = new ArrayList<String>();

	JLabel lblPatchDone = new JLabel("");
	JLabel lbl300PatchDone = new JLabel("");
	//JLabel lblARRNames = new JLabel("");
	private final NoneSelectedButtonGroup buttonGroupPatches = new NoneSelectedButtonGroup();
	private final NoneSelectedButtonGroup buttonGroupBundles = new NoneSelectedButtonGroup();
	private final NoneSelectedButtonGroup buttonGroupSetfiles = new NoneSelectedButtonGroup();


	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		
		try {
		    for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
		        if ("Nimbus".equals(info.getName())) {
		            UIManager.setLookAndFeel(info.getClassName());
		            break;
		        }
		    }
		} catch (Exception e) {
		    // If Nimbus is not available, fall back to cross-platform
		    try {
		        UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
		    } catch (Exception ex) {
		        // not worth my time
		    }
		}
		
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainWindow frame = new MainWindow();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public MainWindow() {
		setTitle("POD HD Converter");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 600, 550);
				
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu mnMenu = new JMenu("Menu");
		menuBar.add(mnMenu);
		
		JMenuItem mntmNewMenuItem = new JMenuItem("Open");
		mntmNewMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				openDialog("desktop");
				tf300Directory.setText(dir.getAbsolutePath());
			}
		});
		mnMenu.add(mntmNewMenuItem);
		
		JMenuItem mntmQuit = new JMenuItem("Quit");
		mntmQuit.addActionListener(new exitApp());
		mnMenu.add(mntmQuit);
		
		JMenu mnHelp = new JMenu("Help");
		menuBar.add(mnHelp);
		
		JMenuItem mntmAbout = new JMenuItem("About");
		mnHelp.add(mntmAbout);
		mntmAbout.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
                JDialog myAboutDialog = new AboutDialog();
                myAboutDialog.setVisible(true);
			}
		});
		
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setBounds(0, 0, 600, 507);
		GridBagConstraints gbc_tabbedPane = new GridBagConstraints();
		gbc_tabbedPane.gridheight = 21;
		gbc_tabbedPane.gridwidth = 13;
		gbc_tabbedPane.insets = new Insets(0, 0, 5, 0);
		gbc_tabbedPane.fill = GridBagConstraints.BOTH;
		gbc_tabbedPane.gridx = 0;
		gbc_tabbedPane.gridy = 0;
		contentPane.add(tabbedPane);
		
		hddesktop = new JPanel();
		tabbedPane.addTab("HD Desktop", null, hddesktop, null);
		GridBagLayout gbl_hddesktop = new GridBagLayout();
		gbl_hddesktop.rowHeights = new int[]{35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_hddesktop.columnWeights = new double[]{0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
		gbl_hddesktop.columnWidths = new int[]{0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{38, 44, 71, 88, 16, 0, 14, 0, 0, 0, 120, 0, 0, 0};
		gbl_contentPane.rowHeights = new int[]{29, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0};
		gbl_contentPane.columnWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		hddesktop.setLayout(gbl_hddesktop);
		
		JPanel hd300 = new JPanel();
		tabbedPane.addTab("HD 300 & 400", null, hd300, null);
		GridBagLayout gbl_hd300 = new GridBagLayout();
		gbl_hd300.columnWidths = new int[]{0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_hd300.rowHeights = new int[]{35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_hd300.columnWeights = new double[]{0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
		hd300.setLayout(gbl_hd300);
		
		JLabel lbl300Header = new JLabel("Translate POD HD 500 Presets to POD HD 300 / HD 400 Presets");
		GridBagConstraints gbc_lbl300Header = new GridBagConstraints();
		gbc_lbl300Header.gridwidth = 13;
		gbc_lbl300Header.insets = new Insets(0, 0, 5, 0);
		gbc_lbl300Header.gridx = 0;
		gbc_lbl300Header.gridy = 0;
		hd300.add(lbl300Header, gbc_lbl300Header);
		
		Component hsDirChooser300 = Box.createHorizontalStrut(20);
		GridBagConstraints gbc_hsDirChooser300 = new GridBagConstraints();
		gbc_hsDirChooser300.insets = new Insets(0, 0, 5, 5);
		gbc_hsDirChooser300.gridx = 0;
		gbc_hsDirChooser300.gridy = 1;
		hd300.add(hsDirChooser300, gbc_hsDirChooser300);
		
		tf300Directory = new JTextField();
		tf300Directory.setText("Choose a directory with presets");
		GridBagConstraints gbc_tf300Directory = new GridBagConstraints();
		gbc_tf300Directory.insets = new Insets(0, 0, 5, 5);
		gbc_tf300Directory.gridwidth = 10;
		gbc_tf300Directory.fill = GridBagConstraints.HORIZONTAL;
		gbc_tf300Directory.gridx = 2;
		gbc_tf300Directory.gridy = 1;
		hd300.add(tf300Directory, gbc_tf300Directory);
		tf300Directory.setColumns(10);
		tf300Directory.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				setDirectory("300");
            }
		});
		
		JButton btn300Browse = new JButton("Browse");
		GridBagConstraints gbc_btn300Browse = new GridBagConstraints();
		gbc_btn300Browse.anchor = GridBagConstraints.WEST;
		gbc_btn300Browse.insets = new Insets(0, 0, 5, 0);
		gbc_btn300Browse.gridx = 12;
		gbc_btn300Browse.gridy = 1;
		hd300.add(btn300Browse, gbc_btn300Browse);
		btn300Browse.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				openDialog("300");
			}
		});
		
		Component vsDirChooser300 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsDirChooser300 = new GridBagConstraints();
		gbc_vsDirChooser300.insets = new Insets(0, 0, 5, 5);
		gbc_vsDirChooser300.gridx = 2;
		gbc_vsDirChooser300.gridy = 2;
		hd300.add(vsDirChooser300, gbc_vsDirChooser300);
		
		JLabel lbl300hd300 = new JLabel("HD 300");
		GridBagConstraints gbc_lbl300hd300 = new GridBagConstraints();
		gbc_lbl300hd300.gridwidth = 2;
		gbc_lbl300hd300.insets = new Insets(0, 0, 5, 5);
		gbc_lbl300hd300.gridx = 3;
		gbc_lbl300hd300.gridy = 3;
		hd300.add(lbl300hd300, gbc_lbl300hd300);
		
		JLabel lbl300hd400 = new JLabel("HD 400");
		GridBagConstraints gbc_lbl300hd400 = new GridBagConstraints();
		gbc_lbl300hd400.gridwidth = 2;
		gbc_lbl300hd400.insets = new Insets(0, 0, 5, 5);
		gbc_lbl300hd400.gridx = 9;
		gbc_lbl300hd400.gridy = 3;
		hd300.add(lbl300hd400, gbc_lbl300hd400);
		
		JLabel lbl300Patches = new JLabel("Patches:");
		GridBagConstraints gbc_lbl300Patches = new GridBagConstraints();
		gbc_lbl300Patches.anchor = GridBagConstraints.WEST;
		gbc_lbl300Patches.gridwidth = 2;
		gbc_lbl300Patches.insets = new Insets(0, 0, 5, 5);
		gbc_lbl300Patches.gridx = 3;
		gbc_lbl300Patches.gridy = 5;
		hd300.add(lbl300Patches, gbc_lbl300Patches);
		
		JSeparator separator300 = new JSeparator();
		separator300.setOrientation(SwingConstants.VERTICAL);
		separator300.setForeground(Color.BLACK);
		GridBagConstraints gbc_separator300 = new GridBagConstraints();
		gbc_separator300.anchor = GridBagConstraints.WEST;
		gbc_separator300.fill = GridBagConstraints.VERTICAL;
		gbc_separator300.gridheight = 14;
		gbc_separator300.insets = new Insets(0, 0, 5, 5);
		gbc_separator300.gridx = 6;
		gbc_separator300.gridy = 3;
		hd300.add(separator300, gbc_separator300);
		
		GridBagConstraints gbc_chckbx300PatchH5e = new GridBagConstraints();
		gbc_chckbx300PatchH5e.anchor = GridBagConstraints.WEST;
		gbc_chckbx300PatchH5e.gridwidth = 4;
		gbc_chckbx300PatchH5e.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx300PatchH5e.gridx = 2;
		gbc_chckbx300PatchH5e.gridy = 6;
		hd300.add(chckbx300PatchH5e, gbc_chckbx300PatchH5e);
		
		GridBagConstraints gbc_chckbx400PatchH5e = new GridBagConstraints();
		gbc_chckbx400PatchH5e.gridwidth = 4;
		gbc_chckbx400PatchH5e.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx400PatchH5e.gridx = 8;
		gbc_chckbx400PatchH5e.gridy = 6;
		hd300.add(chckbx400PatchH5e, gbc_chckbx400PatchH5e);
		
		Component vsPatchesBundles300 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsPatchesBundles300 = new GridBagConstraints();
		gbc_vsPatchesBundles300.insets = new Insets(0, 0, 5, 5);
		gbc_vsPatchesBundles300.gridx = 2;
		gbc_vsPatchesBundles300.gridy = 7;
		hd300.add(vsPatchesBundles300, gbc_vsPatchesBundles300);
		
		JLabel lbl300Bundles = new JLabel("Bundles:");
		GridBagConstraints gbc_lbl300Bundles = new GridBagConstraints();
		gbc_lbl300Bundles.anchor = GridBagConstraints.WEST;
		gbc_lbl300Bundles.gridwidth = 2;
		gbc_lbl300Bundles.insets = new Insets(0, 0, 5, 5);
		gbc_lbl300Bundles.gridx = 3;
		gbc_lbl300Bundles.gridy = 8;
		hd300.add(lbl300Bundles, gbc_lbl300Bundles);
		GridBagConstraints gbc_chckbx400PatchH5b = new GridBagConstraints();
		gbc_chckbx400PatchH5b.gridwidth = 4;
		gbc_chckbx400PatchH5b.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx400PatchH5b.gridx = 8;
		gbc_chckbx400PatchH5b.gridy = 9;
		hd300.add(chckbx400PatchH5b, gbc_chckbx400PatchH5b);
		GridBagConstraints gbc_chckbx300PatchH5b = new GridBagConstraints();
		gbc_chckbx300PatchH5b.anchor = GridBagConstraints.WEST;
		gbc_chckbx300PatchH5b.gridwidth = 4;
		gbc_chckbx300PatchH5b.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx300PatchH5b.gridx = 2;
		gbc_chckbx300PatchH5b.gridy = 9;
		hd300.add(chckbx300PatchH5b, gbc_chckbx300PatchH5b);
		lPatchCheckboxes300.add(chckbx300PatchH5b);
		
		Component vsBundlesSetlists300 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsBundlesSetlists300 = new GridBagConstraints();
		gbc_vsBundlesSetlists300.insets = new Insets(0, 0, 5, 5);
		gbc_vsBundlesSetlists300.gridx = 2;
		gbc_vsBundlesSetlists300.gridy = 10;
		hd300.add(vsBundlesSetlists300, gbc_vsBundlesSetlists300);
		
		JLabel lbl300Setlists = new JLabel("Setlists:");
		GridBagConstraints gbc_lbl300Setlists = new GridBagConstraints();
		gbc_lbl300Setlists.anchor = GridBagConstraints.WEST;
		gbc_lbl300Setlists.gridwidth = 2;
		gbc_lbl300Setlists.insets = new Insets(0, 0, 5, 5);
		gbc_lbl300Setlists.gridx = 3;
		gbc_lbl300Setlists.gridy = 11;
		hd300.add(lbl300Setlists, gbc_lbl300Setlists);
		GridBagConstraints gbc_chckbx300PatchH5s = new GridBagConstraints();
		gbc_chckbx300PatchH5s.anchor = GridBagConstraints.WEST;
		gbc_chckbx300PatchH5s.gridwidth = 4;
		gbc_chckbx300PatchH5s.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx300PatchH5s.gridx = 2;
		gbc_chckbx300PatchH5s.gridy = 12;
		hd300.add(chckbx300PatchH5s, gbc_chckbx300PatchH5s);
		GridBagConstraints gbc_chckbx400PatchH5s = new GridBagConstraints();
		gbc_chckbx400PatchH5s.gridwidth = 4;
		gbc_chckbx400PatchH5s.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx400PatchH5s.gridx = 8;
		gbc_chckbx400PatchH5s.gridy = 12;
		hd300.add(chckbx400PatchH5s, gbc_chckbx400PatchH5s);
		
		Component vsSetlistsBackup300 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsSetlistsBackup300 = new GridBagConstraints();
		gbc_vsSetlistsBackup300.insets = new Insets(0, 0, 5, 5);
		gbc_vsSetlistsBackup300.gridx = 2;
		gbc_vsSetlistsBackup300.gridy = 14;
		hd300.add(vsSetlistsBackup300, gbc_vsSetlistsBackup300);
		
		JLabel lblNewLabel_2 = new JLabel("General:");
		GridBagConstraints gbc_lblNewLabel_2 = new GridBagConstraints();
		gbc_lblNewLabel_2.anchor = GridBagConstraints.WEST;
		gbc_lblNewLabel_2.gridwidth = 2;
		gbc_lblNewLabel_2.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_2.gridx = 3;
		gbc_lblNewLabel_2.gridy = 15;
		hd300.add(lblNewLabel_2, gbc_lblNewLabel_2);
		
		chckbx300Backup.setSelected(true);
		GridBagConstraints gbc_chckbx300Backup = new GridBagConstraints();
		gbc_chckbx300Backup.anchor = GridBagConstraints.WEST;
		gbc_chckbx300Backup.gridwidth = 4;
		gbc_chckbx300Backup.insets = new Insets(0, 0, 5, 5);
		gbc_chckbx300Backup.gridx = 2;
		gbc_chckbx300Backup.gridy = 16;
		hd300.add(chckbx300Backup, gbc_chckbx300Backup);
		
		GridBagConstraints gbc_lbl300PatchDone = new GridBagConstraints();
		gbc_lbl300PatchDone.gridwidth = 10;
		gbc_lbl300PatchDone.insets = new Insets(0, 0, 0, 5);
		gbc_lbl300PatchDone.gridx = 2;
		gbc_lbl300PatchDone.gridy = 17;
		hd300.add(lbl300PatchDone, gbc_lbl300PatchDone);

		JPanel advancedPanel = new JPanel();
		tabbedPane.addTab("Advanced", null, advancedPanel, null);
		GridBagLayout gbl_advancedPanel = new GridBagLayout();
		gbl_advancedPanel.columnWidths = new int[]{0, 0, 20, 0, 0, 0, 0, 0, 0, 0};
		gbl_advancedPanel.rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		gbl_advancedPanel.columnWeights = new double[]{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, Double.MIN_VALUE};
		gbl_advancedPanel.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		advancedPanel.setLayout(gbl_advancedPanel);
		
		Component verticalStrut_5 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_verticalStrut_5 = new GridBagConstraints();
		gbc_verticalStrut_5.anchor = GridBagConstraints.WEST;
		gbc_verticalStrut_5.insets = new Insets(0, 0, 5, 5);
		gbc_verticalStrut_5.gridx = 2;
		gbc_verticalStrut_5.gridy = 0;
		advancedPanel.add(verticalStrut_5, gbc_verticalStrut_5);
		
		JLabel lblInput = new JLabel("Edit Presets (HD Desktop):");
		GridBagConstraints gbc_lblInput = new GridBagConstraints();
		gbc_lblInput.gridwidth = 3;
		gbc_lblInput.anchor = GridBagConstraints.WEST;
		gbc_lblInput.insets = new Insets(0, 0, 5, 5);
		gbc_lblInput.gridx = 2;
		gbc_lblInput.gridy = 1;
		advancedPanel.add(lblInput, gbc_lblInput);
		chckbxEditInputs.setToolTipText("You'll have to set 'Input Setup' on your POD HD to \"Preset\" (insted of \"Global\") to see effects.");
		chckbxEditInputs.setSelected(false);
		chckbxEditInputs.addItemListener(new ItemListener() {
			@Override
			public void itemStateChanged(ItemEvent e) {
				if(e.getStateChange() == ItemEvent.SELECTED){
					cbSourceOne.setEnabled(chckbxEditInputs.isSelected());
					cbSourceTwo.setEnabled(chckbxEditInputs.isSelected());
					cbGuitarIn.setEnabled(chckbxEditInputs.isSelected());
				} else {
					cbSourceOne.setEnabled(false);
					cbSourceTwo.setEnabled(false);
					cbGuitarIn.setEnabled(false);
				}
			}
		});
		GridBagConstraints gbc_chckbxEditInputs = new GridBagConstraints();
		gbc_chckbxEditInputs.anchor = GridBagConstraints.WEST;
		gbc_chckbxEditInputs.gridwidth = 2;
		gbc_chckbxEditInputs.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxEditInputs.gridx = 2;
		gbc_chckbxEditInputs.gridy = 3;
		advancedPanel.add(chckbxEditInputs, gbc_chckbxEditInputs);
		
		JLabel lblInputOne = new JLabel("Input Source 1");
		GridBagConstraints gbc_lblInputOne = new GridBagConstraints();
		gbc_lblInputOne.anchor = GridBagConstraints.WEST;
		gbc_lblInputOne.insets = new Insets(0, 0, 5, 5);
		gbc_lblInputOne.gridx = 3;
		gbc_lblInputOne.gridy = 4;
		advancedPanel.add(lblInputOne, gbc_lblInputOne);
		
		Component horizontalStrut = Box.createHorizontalStrut(20);
		GridBagConstraints gbc_horizontalStrut = new GridBagConstraints();
		gbc_horizontalStrut.insets = new Insets(0, 0, 5, 5);
		gbc_horizontalStrut.gridx = 5;
		gbc_horizontalStrut.gridy = 4;
		advancedPanel.add(horizontalStrut, gbc_horizontalStrut);
		
		JLabel lblInputTwo = new JLabel("Input Source 2");
		GridBagConstraints gbc_lblInputTwo = new GridBagConstraints();
		gbc_lblInputTwo.insets = new Insets(0, 0, 5, 5);
		gbc_lblInputTwo.gridx = 6;
		gbc_lblInputTwo.gridy = 4;
		advancedPanel.add(lblInputTwo, gbc_lblInputTwo);
		
		cbSourceOne.setSelectedIndex(0);
		GridBagConstraints gbc_cbSourceOne = new GridBagConstraints();
		gbc_cbSourceOne.anchor = GridBagConstraints.WEST;
		gbc_cbSourceOne.insets = new Insets(0, 0, 5, 5);
		gbc_cbSourceOne.gridx = 4;
		gbc_cbSourceOne.gridy = 5;
		cbSourceOne.setEnabled(false);
		advancedPanel.add(cbSourceOne, gbc_cbSourceOne);
		
		cbSourceTwo.setSelectedIndex(0);
		GridBagConstraints gbc_cbSourceTwo = new GridBagConstraints();
		gbc_cbSourceTwo.insets = new Insets(0, 0, 5, 5);
		gbc_cbSourceTwo.fill = GridBagConstraints.HORIZONTAL;
		gbc_cbSourceTwo.gridx = 7;
		gbc_cbSourceTwo.gridy = 5;
		cbSourceTwo.setEnabled(false);
		advancedPanel.add(cbSourceTwo, gbc_cbSourceTwo);
		
		Component horizontalStrut_1 = Box.createHorizontalStrut(20);
		GridBagConstraints gbc_horizontalStrut_1 = new GridBagConstraints();
		gbc_horizontalStrut_1.insets = new Insets(0, 0, 5, 0);
		gbc_horizontalStrut_1.gridx = 8;
		gbc_horizontalStrut_1.gridy = 5;
		advancedPanel.add(horizontalStrut_1, gbc_horizontalStrut_1);
		
		JLabel lblGuitarIn = new JLabel("Guitar IN-Z");
		GridBagConstraints gbc_lblGuitarIn = new GridBagConstraints();
		gbc_lblGuitarIn.anchor = GridBagConstraints.WEST;
		gbc_lblGuitarIn.insets = new Insets(0, 0, 5, 5);
		gbc_lblGuitarIn.gridx = 3;
		gbc_lblGuitarIn.gridy = 6;
		advancedPanel.add(lblGuitarIn, gbc_lblGuitarIn);
		
		cbGuitarIn.setSelectedIndex(0);
		GridBagConstraints gbc_cbGuitarIn = new GridBagConstraints();
		gbc_cbGuitarIn.anchor = GridBagConstraints.WEST;
		gbc_cbGuitarIn.insets = new Insets(0, 0, 5, 5);
		gbc_cbGuitarIn.gridx = 4;
		gbc_cbGuitarIn.gridy = 7;
		cbGuitarIn.setEnabled(false);
		advancedPanel.add(cbGuitarIn, gbc_cbGuitarIn);
		
		Component verticalStrut_4 = Box.createVerticalStrut(20);
		GridBagConstraints gbc_verticalStrut_4 = new GridBagConstraints();
		gbc_verticalStrut_4.anchor = GridBagConstraints.WEST;
		gbc_verticalStrut_4.insets = new Insets(0, 0, 5, 5);
		gbc_verticalStrut_4.gridx = 3;
		gbc_verticalStrut_4.gridy = 10;
		advancedPanel.add(verticalStrut_4, gbc_verticalStrut_4);
		
		JLabel lblEditInfo = new JLabel("<html>Enabling any checkbox will change the given parameter in any file <br>(Presets, Setlists, Bundles) that matches the convert pattern in the <br>\"HD Desktop\" Tab.</html>");
		lblEditInfo.setHorizontalAlignment(SwingConstants.LEFT);
		lblEditInfo.setVerticalAlignment(SwingConstants.TOP);
		GridBagConstraints gbc_lblEditInfo = new GridBagConstraints();
		gbc_lblEditInfo.fill = GridBagConstraints.BOTH;
		gbc_lblEditInfo.gridheight = 3;
		gbc_lblEditInfo.anchor = GridBagConstraints.NORTHWEST;
		gbc_lblEditInfo.gridwidth = 6;
		gbc_lblEditInfo.insets = new Insets(0, 0, 0, 5);
		gbc_lblEditInfo.gridx = 2;
		gbc_lblEditInfo.gridy = 14;
		advancedPanel.add(lblEditInfo, gbc_lblEditInfo);
		
		JLabel mainLabel = new JLabel("Convert POD HD 500 Presets to POD HD Desktop Presets");
		mainLabel.setHorizontalAlignment(SwingConstants.CENTER);
		GridBagConstraints gbc_mainLabel = new GridBagConstraints();
		gbc_mainLabel.gridwidth = 13;
		gbc_mainLabel.insets = new Insets(0, 0, 5, 0);
		gbc_mainLabel.gridx = 0;
		gbc_mainLabel.gridy = 0;
		hddesktop.add(mainLabel, gbc_mainLabel);
		
		JButton btnBrowse = new JButton("Browse");
		btnBrowse.setToolTipText("Click to choose a directoy");
		btnBrowse.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				openDialog("desktop");
			}
		});
		
		Component hsDirChooser = Box.createHorizontalStrut(20);
		GridBagConstraints gbc_hsDirChooser = new GridBagConstraints();
		gbc_hsDirChooser.insets = new Insets(0, 0, 5, 5);
		gbc_hsDirChooser.gridx = 0;
		gbc_hsDirChooser.gridy = 1;
		hddesktop.add(hsDirChooser, gbc_hsDirChooser);
		
		// txtFileChooser - "Select Directory" Label
		txtFileChooser = new JTextField();
		txtFileChooser.setText("Choose a directory with presets");
		GridBagConstraints gbc_txtFileChooser = new GridBagConstraints();
		gbc_txtFileChooser.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtFileChooser.gridwidth = 10;
		gbc_txtFileChooser.insets = new Insets(0, 0, 5, 5);
		gbc_txtFileChooser.gridx = 2;
		gbc_txtFileChooser.gridy = 1;
		hddesktop.add(txtFileChooser, gbc_txtFileChooser);
		txtFileChooser.setColumns(10);
		txtFileChooser.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				setDirectory("desktop");
            }
		});
		GridBagConstraints gbc_btnBrowse = new GridBagConstraints();
		gbc_btnBrowse.insets = new Insets(0, 0, 5, 0);
		gbc_btnBrowse.anchor = GridBagConstraints.NORTHWEST;
		gbc_btnBrowse.gridx = 12;
		gbc_btnBrowse.gridy = 1;
		hddesktop.add(btnBrowse, gbc_btnBrowse);
		
		Component vsDirChooser = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsDirChooser = new GridBagConstraints();
		gbc_vsDirChooser.insets = new Insets(0, 0, 5, 5);
		gbc_vsDirChooser.gridx = 3;
		gbc_vsDirChooser.gridy = 2;
		hddesktop.add(vsDirChooser, gbc_vsDirChooser);
				
		JLabel lblPatches = new JLabel("Patches:");
		lblPatches.setForeground(Color.BLACK);
		GridBagConstraints gbc_lblPatches = new GridBagConstraints();
		gbc_lblPatches.anchor = GridBagConstraints.WEST;
		gbc_lblPatches.gridwidth = 2;
		gbc_lblPatches.insets = new Insets(0, 0, 5, 5);
		gbc_lblPatches.gridx = 3;
		gbc_lblPatches.gridy = 3;
		hddesktop.add(lblPatches, gbc_lblPatches);
		chckbxH5e.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			}
		});
		
		//chckbxH5e
		chckbxH5e.setHorizontalAlignment(SwingConstants.LEFT);
		chckbxH5e.setSelected(true);
		//chckbxH5e.setToolTipText("Modify .h5e files (-> change their inputs) to make them load with POD HD");
		GridBagConstraints gbc_chckbxH5e = new GridBagConstraints();
		gbc_chckbxH5e.gridwidth = 4;
		gbc_chckbxH5e.anchor = GridBagConstraints.WEST;
		gbc_chckbxH5e.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxH5e.gridx = 2;
		gbc_chckbxH5e.gridy = 4;
		hddesktop.add(chckbxH5e, gbc_chckbxH5e);
		chckbxRenameH5e.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			}
		});
		
		JSeparator separator = new JSeparator();
		separator.setForeground(Color.BLACK);
		separator.setOrientation(SwingConstants.VERTICAL);
		GridBagConstraints gbc_separator = new GridBagConstraints();
		gbc_separator.anchor = GridBagConstraints.WEST;
		gbc_separator.fill = GridBagConstraints.VERTICAL;
		gbc_separator.gridheight = 14;
		gbc_separator.insets = new Insets(0, 0, 5, 5);
		gbc_separator.gridx = 6;
		gbc_separator.gridy = 3;
		hddesktop.add(separator, gbc_separator);
		
		//chckbxRenameH5e
		chckbxRenameH5e.setSelected(true);
		//chckbxRenameH5e.setToolTipText("Rename .h5e files to .hbe (-> loadable with POD HD Desktop Edit software)");
		GridBagConstraints gbc_chckbxRenameH5e = new GridBagConstraints();
		gbc_chckbxRenameH5e.gridwidth = 4;
		gbc_chckbxRenameH5e.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameH5e.gridx = 8;
		gbc_chckbxRenameH5e.gridy = 4;
		buttonGroupPatches.add(chckbxRenameH5e);
		hddesktop.add(chckbxRenameH5e, gbc_chckbxRenameH5e);
		chckbxHbe.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			}
		});
				
		//chckbxH5e
		chckbxHbe.setHorizontalAlignment(SwingConstants.LEFT);
		chckbxHbe.setSelected(true);
		//chckbxHbe.setToolTipText("Modify .hbe files (-> change their inputs) to make them load with POD HD");
		GridBagConstraints gbc_chckbxHbe = new GridBagConstraints();
		gbc_chckbxHbe.gridwidth = 4;
		gbc_chckbxHbe.anchor = GridBagConstraints.WEST;
		gbc_chckbxHbe.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxHbe.gridx = 2;
		gbc_chckbxHbe.gridy = 5;
		hddesktop.add(chckbxHbe, gbc_chckbxHbe);
				
		//chckbxRenameHbe
		//chckbxRenameHbe.setToolTipText("Rename .hbe files to .h5e (-> loadable with POD HD 500 Edit software)");
		GridBagConstraints gbc_chckbxRenameHbe = new GridBagConstraints();
		gbc_chckbxRenameHbe.gridwidth = 4;
		gbc_chckbxRenameHbe.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameHbe.gridx = 8;
		gbc_chckbxRenameHbe.gridy = 5;
		buttonGroupPatches.add(chckbxRenameHbe);
		chckbxRenameHbe.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			}
		});
		hddesktop.add(chckbxRenameHbe, gbc_chckbxRenameHbe);
		
		Component vsPatchBundles = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsPatchBundles = new GridBagConstraints();
		gbc_vsPatchBundles.insets = new Insets(0, 0, 5, 5);
		gbc_vsPatchBundles.gridx = 2;
		gbc_vsPatchBundles.gridy = 6;
		hddesktop.add(vsPatchBundles, gbc_vsPatchBundles);
		
		JLabel lblBundles = new JLabel("Bundles:");
		GridBagConstraints gbc_lblBundles = new GridBagConstraints();
		gbc_lblBundles.anchor = GridBagConstraints.WEST;
		gbc_lblBundles.gridwidth = 2;
		gbc_lblBundles.insets = new Insets(0, 0, 5, 5);
		gbc_lblBundles.gridx = 3;
		gbc_lblBundles.gridy = 7;
		hddesktop.add(lblBundles, gbc_lblBundles);
		
		//chckbxH5b
		chckbxH5b.setSelected(true);
		GridBagConstraints gbc_chckbxH5b = new GridBagConstraints();
		gbc_chckbxH5b.anchor = GridBagConstraints.WEST;
		gbc_chckbxH5b.gridwidth = 4;
		gbc_chckbxH5b.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxH5b.gridx = 2;
		gbc_chckbxH5b.gridy = 8;
		hddesktop.add(chckbxH5b, gbc_chckbxH5b);
		
		//chckbxRenameH5b
		chckbxRenameH5b.setSelected(true);
		GridBagConstraints gbc_chckbxRenameH5b = new GridBagConstraints();
		gbc_chckbxRenameH5b.gridwidth = 4;
		gbc_chckbxRenameH5b.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameH5b.gridx = 8;
		gbc_chckbxRenameH5b.gridy = 8;
		buttonGroupBundles.add(chckbxRenameH5b);
		hddesktop.add(chckbxRenameH5b, gbc_chckbxRenameH5b);
		
		//chckbxHbb
		chckbxHbb.setSelected(true);
		GridBagConstraints gbc_chckbxHbb = new GridBagConstraints();
		gbc_chckbxHbb.anchor = GridBagConstraints.WEST;
		gbc_chckbxHbb.gridwidth = 4;
		gbc_chckbxHbb.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxHbb.gridx = 2;
		gbc_chckbxHbb.gridy = 9;
		hddesktop.add(chckbxHbb, gbc_chckbxHbb);
		
		//chckbxRenameHbb
		GridBagConstraints gbc_chckbxRenameHbb = new GridBagConstraints();
		gbc_chckbxRenameHbb.gridwidth = 4;
		gbc_chckbxRenameHbb.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameHbb.gridx = 8;
		gbc_chckbxRenameHbb.gridy = 9;
		buttonGroupBundles.add(chckbxRenameHbb);
		hddesktop.add(chckbxRenameHbb, gbc_chckbxRenameHbb);
		
		Component vsBundlesSetlists = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsBundlesSetlists = new GridBagConstraints();
		gbc_vsBundlesSetlists.insets = new Insets(0, 0, 5, 5);
		gbc_vsBundlesSetlists.gridx = 3;
		gbc_vsBundlesSetlists.gridy = 10;
		hddesktop.add(vsBundlesSetlists, gbc_vsBundlesSetlists);
		
		JLabel lblSetlists = new JLabel("Setlists:");
		GridBagConstraints gbc_lblSetlists = new GridBagConstraints();
		gbc_lblSetlists.anchor = GridBagConstraints.WEST;
		gbc_lblSetlists.gridwidth = 2;
		gbc_lblSetlists.insets = new Insets(0, 0, 5, 5);
		gbc_lblSetlists.gridx = 3;
		gbc_lblSetlists.gridy = 11;
		hddesktop.add(lblSetlists, gbc_lblSetlists);
		
		//chckbxH5s
		chckbxH5s.setSelected(true);
		GridBagConstraints gbc_chckbxH5s = new GridBagConstraints();
		gbc_chckbxH5s.anchor = GridBagConstraints.WEST;
		gbc_chckbxH5s.gridwidth = 4;
		gbc_chckbxH5s.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxH5s.gridx = 2;
		gbc_chckbxH5s.gridy = 12;
		hddesktop.add(chckbxH5s, gbc_chckbxH5s);
		
		//chckbxRenameH5s
		chckbxRenameH5s.setSelected(true);
		GridBagConstraints gbc_chckbxRenameH5s = new GridBagConstraints();
		gbc_chckbxRenameH5s.gridwidth = 4;
		gbc_chckbxRenameH5s.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameH5s.gridx = 8;
		gbc_chckbxRenameH5s.gridy = 12;
		buttonGroupSetfiles.add(chckbxRenameH5s);
		hddesktop.add(chckbxRenameH5s, gbc_chckbxRenameH5s);
		
		//chckbxHbs
		chckbxHbs.setSelected(true);
		GridBagConstraints gbc_chckbxHbs = new GridBagConstraints();
		gbc_chckbxHbs.anchor = GridBagConstraints.WEST;
		gbc_chckbxHbs.gridwidth = 4;
		gbc_chckbxHbs.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxHbs.gridx = 2;
		gbc_chckbxHbs.gridy = 13;
		hddesktop.add(chckbxHbs, gbc_chckbxHbs);
		
		//chckbxRenameHbs
		GridBagConstraints gbc_chckbxRenameHbs = new GridBagConstraints();
		gbc_chckbxRenameHbs.gridwidth = 4;
		gbc_chckbxRenameHbs.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxRenameHbs.gridx = 8;
		gbc_chckbxRenameHbs.gridy = 13;
		buttonGroupSetfiles.add(chckbxRenameHbs);
		hddesktop.add(chckbxRenameHbs, gbc_chckbxRenameHbs);
		
		Component vsSetlistsGeneral = Box.createVerticalStrut(20);
		GridBagConstraints gbc_vsSetlistsGeneral = new GridBagConstraints();
		gbc_vsSetlistsGeneral.insets = new Insets(0, 0, 5, 5);
		gbc_vsSetlistsGeneral.gridx = 3;
		gbc_vsSetlistsGeneral.gridy = 14;
		hddesktop.add(vsSetlistsGeneral, gbc_vsSetlistsGeneral);
		
		JLabel lblGeneral = new JLabel("General:");
		GridBagConstraints gbc_lblGeneral = new GridBagConstraints();
		gbc_lblGeneral.anchor = GridBagConstraints.WEST;
		gbc_lblGeneral.gridwidth = 2;
		gbc_lblGeneral.insets = new Insets(0, 0, 5, 5);
		gbc_lblGeneral.gridx = 3;
		gbc_lblGeneral.gridy = 15;
		hddesktop.add(lblGeneral, gbc_lblGeneral);
		
		//chckbxBackup
		chckbxBackup.setHorizontalAlignment(SwingConstants.LEFT);
		chckbxBackup.setSelected(true);
		//chckbxBackup.setToolTipText("Create Backup of files selected to be modified");
		GridBagConstraints gbc_chckbxBackup = new GridBagConstraints();
		gbc_chckbxBackup.gridwidth = 4;
		gbc_chckbxBackup.anchor = GridBagConstraints.WEST;
		gbc_chckbxBackup.insets = new Insets(0, 0, 5, 5);
		gbc_chckbxBackup.gridx = 2;
		gbc_chckbxBackup.gridy = 16;
		hddesktop.add(chckbxBackup, gbc_chckbxBackup);
		chckbxBackup.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			}
		});
		
		//GridBagConstraints gbc_lblARRNames = new GridBagConstraints();
		//gbc_lblARRNames.anchor = GridBagConstraints.EAST;
		//gbc_lblARRNames.gridwidth = 3;
		//gbc_lblARRNames.insets = new Insets(0, 0, 0, 5);
		//gbc_lblARRNames.gridx = 8;
		//gbc_lblARRNames.gridy = 7;
		//contentPanel.add(lblARRNames, gbc_lblARRNames);
				
		GridBagConstraints gbc_lblPatchDone = new GridBagConstraints();
		gbc_lblPatchDone.anchor = GridBagConstraints.WEST;
		gbc_lblPatchDone.gridwidth = 10;
		gbc_lblPatchDone.fill = GridBagConstraints.VERTICAL;
		gbc_lblPatchDone.insets = new Insets(0, 0, 0, 5);
		gbc_lblPatchDone.gridx = 2;
		gbc_lblPatchDone.gridy = 17;
		hddesktop.add(lblPatchDone, gbc_lblPatchDone);
		
		JButton btnRun = new JButton("Run");
		btnRun.setToolTipText("Click to perform checkmarked operations on selected directory");
		btnRun.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				copyFiles("Desktop");
				processAdvancedTab();
		        modify(dir);
                changeText();
                renameFile();
            }
		});
		GridBagConstraints gbc_btnRun = new GridBagConstraints();
		gbc_btnRun.gridx = 12;
		gbc_btnRun.gridy = 17;
		hddesktop.add(btnRun, gbc_btnRun);
		hddesktop.getRootPane().setDefaultButton(btnRun);
			
		JButton btn300Run = new JButton("Run");
		GridBagConstraints gbc_btn300Run = new GridBagConstraints();
		gbc_btn300Run.anchor = GridBagConstraints.WEST;
		gbc_btn300Run.gridx = 12;
		gbc_btn300Run.gridy = 17;
		hd300.add(btn300Run, gbc_btn300Run);
		btn300Run.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				copyFiles("300");
				createEmptyPreset();
				//processAdvancedTab();
				modify300(dir);
				changeText300();
                //renameFile();
            }
		});
		//hd300.getRootPane().setDefaultButton(btn300Run);
		
		// POD Desktop Converter
		
		lPatchCheckboxes.clear();
		lRenameCheckboxes.clear();
		lFileExtension.clear();
		lFileExtensionReverse.clear();

		lPatchCheckboxes.add(chckbxH5e);
		lPatchCheckboxes.add(chckbxHbe);
		lPatchCheckboxes.add(chckbxH5b);
		lPatchCheckboxes.add(chckbxHbb);
		lPatchCheckboxes.add(chckbxH5s);
		lPatchCheckboxes.add(chckbxHbs);
	
		lRenameCheckboxes.add(chckbxRenameH5e);
		lRenameCheckboxes.add(chckbxRenameHbe);
		lRenameCheckboxes.add(chckbxRenameH5b);
		lRenameCheckboxes.add(chckbxRenameHbb);
		lRenameCheckboxes.add(chckbxRenameH5s);
		lRenameCheckboxes.add(chckbxRenameHbs);
		
		lFileExtension.add(patternH5e);
		lFileExtension.add(patternHbe);
		lFileExtension.add(patternH5b);
		lFileExtension.add(patternHbb);
		lFileExtension.add(patternH5s);
		lFileExtension.add(patternHbs);
		
		lFileExtensionReverse.add(patternHbe);
		lFileExtensionReverse.add(patternH5e);
		lFileExtensionReverse.add(patternHbb);
		lFileExtensionReverse.add(patternH5b);
		lFileExtensionReverse.add(patternHbs);
		lFileExtensionReverse.add(patternH5s);
		
		// POD 300 Converter
		
		lPatchCheckboxes300.clear();
		lPatchCheckboxes400.clear();
		lFileExtension300.clear();
		lFileExtension400.clear();
		lFileExtension300Reverse.clear();
		lFileExtension400Reverse.clear();
		
		lPatchCheckboxes300.add(chckbx300PatchH5e);
		lPatchCheckboxes300.add(chckbx300PatchH5b);
		lPatchCheckboxes300.add(chckbx300PatchH5s);
	
		lPatchCheckboxes400.add(chckbx400PatchH5e);
		lPatchCheckboxes400.add(chckbx400PatchH5b);
		lPatchCheckboxes400.add(chckbx400PatchH5s);
		
		lFileExtension300.add(patternH5e);
		lFileExtension300.add(patternH5b);
		lFileExtension300.add(patternH5s);
		
		lFileExtension300Reverse.add(patternH3e);
		lFileExtension300Reverse.add(patternH3b);
		lFileExtension300Reverse.add(patternH3s);
		
		lFileExtension400.add(patternH5e);
		lFileExtension400.add(patternH5b);
		lFileExtension400.add(patternH5s);
		
		lFileExtension400Reverse.add(patternH4e);
		lFileExtension400Reverse.add(patternH4b);
		lFileExtension400Reverse.add(patternH4s);
		
		chckbx300PatchH5b.setEnabled(false);
		chckbx300PatchH5s.setEnabled(false);
		chckbx400PatchH5b.setEnabled(false);
		chckbx400PatchH5s.setEnabled(false);
	   
	}

    /**
     * @param dir A file object defining the directory for patch modifying
     **/
    public void modify(File dir) {
   
        File listFile[] = dir.listFiles();
        if (listFile != null) {
            for (int i=0; i<listFile.length; i++) {
                if (listFile[i].isDirectory()) {
                    //modify(listFile[i]); // recursive
                } else {
            		try {
            		//	for (int i = 0; i < lPatchCheckboxes.size(); i++) {
            		//		if (lPatchCheckboxes.get(i).isSelected() && listFile[i].getName().endsWith(lFileExtension.get(i))) {
                    //        	modifyPresetFiles(listFile[i], "rw");
            		//		}
            		//	}
            		//
            		// HD Desktop
                    if(chckbxH5e.isSelected() && listFile[i].getName().endsWith(patternH5e)) {
                    	modifyPresetFiles(listFile[i], "rw");
            			}
                    if (chckbxHbe.isSelected() && listFile[i].getName().endsWith(patternHbe)){
                        	modifyPresetFiles(listFile[i], "rw");
            			}
                    if (chckbxH5b.isSelected() && listFile[i].getName().endsWith(patternH5b)){
                        	modifyBundleFiles(listFile[i], "rw");	
            			}
                    if (chckbxHbb.isSelected() && listFile[i].getName().endsWith(patternHbb)){
                        	modifyBundleFiles(listFile[i], "rw");
            			}
                    if (chckbxH5s.isSelected() && listFile[i].getName().endsWith(patternH5s)){
                    	modifySetlistFiles(listFile[i], "rw");
        				}
                    if (chckbxHbs.isSelected() && listFile[i].getName().endsWith(patternHbs)){
                    	modifySetlistFiles(listFile[i], "rw");
        				}                   
                    }
                    catch (Exception e){}
                }
            }
        }
    }
    
    /**
     * @param dir A file object defining the directory for patch modifying
     **/
    public void modify300(File dir) {
    	
    	if (chckbx300PatchH5e.isSelected()) {
            File sourceFiles[] = dir.listFiles(new extFileFilter(patternH5e));
            File targetFiles[] = dir.listFiles(new extFileFilter(patternH3e));
            
            for (int i=0; i<sourceFiles.length; i++) {
            	try {
            		modifyPresetFiles300(sourceFiles[i], targetFiles[i], patternH3e, "rw");
            		}
                catch (Exception e){}
            }
        }
    	if (chckbx400PatchH5e.isSelected()) {
            File sourceFiles[] = dir.listFiles(new extFileFilter(patternH5e));
            File targetFiles[] = dir.listFiles(new extFileFilter(patternH4e));
            
            for (int i=0; i<sourceFiles.length; i++) {
            	try {
            		modifyPresetFiles300(sourceFiles[i], targetFiles[i], patternH4e, "rw");
            		}
                catch (Exception e){}
            }
        }
    	if (chckbx300PatchH5b.isSelected()) {
            File sourceFiles[] = dir.listFiles(new extFileFilter(patternH5b));
            File targetFiles[] = dir.listFiles(new extFileFilter(patternH3b));
            
            for (int i=0; i<sourceFiles.length; i++) {
            	try {
            		modifyBundleFiles300(sourceFiles[i], targetFiles[i], "rw");
            		}
                catch (Exception e){}
            }
        }
    	if (chckbx300PatchH5s.isSelected()) {
            File sourceFiles[] = dir.listFiles(new extFileFilter(patternH5s));
            File targetFiles[] = dir.listFiles(new extFileFilter(patternH3s));
            
            for (int i=0; i<sourceFiles.length; i++) {
            	try {
            		modifySetlistFiles300(sourceFiles[i], targetFiles[i], "rw");
            		}
                catch (Exception e){}
            }
        }
    }
    
   public void openDialog(String pressedFrom) {
		 try{
			 JFileChooser Chooser = new JFileChooser();
			 Chooser.setCurrentDirectory(new java.io.File("."));
			 Chooser.setDialogTitle(choosertitle);
			 Chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			 //
			 //Set FileFilter
			 //
		     FileNameExtensionFilter podFilesFilter = new FileNameExtensionFilter(
		    	        "POD HD 500 and POD HD files", "h5e", "hbe" , "h5b" , "hbb" , "h5s" , "hbs");
		     Chooser.setFileFilter(podFilesFilter);
			 Chooser.showOpenDialog(null);
			 if (pressedFrom.equals("desktop")) {
				 dir = Chooser.getSelectedFile();
					txtFileChooser.setText(dir.getAbsolutePath());
			 } else if (pressedFrom.equals("300")) {
				 dir = Chooser.getSelectedFile();
				 tf300Directory.setText(dir.getAbsolutePath());
			 }
		 }catch (Exception e){
			 e.getStackTrace();
		 }
   }
   
   public void setDirectory(String pressedFrom) {
		 if (pressedFrom.equals("desktop")) {
			   dir = new File(txtFileChooser.getText());
		 } else if (pressedFrom.equals("300")) {
			   dir = new File(tf300Directory.getText());
		 }
   }
   
   public class extFileFilter implements FileFilter {
	   String ext;
	   public extFileFilter(String ext){
		   this.ext = "." + ext;
	   }
	   
	   public boolean accept(File pathname) {
	     if (pathname.getName().endsWith(ext))
	       return true;
	     return false;
	   }
	 }
	
	public class extNameFilter implements FilenameFilter {
		String ext;
		public extNameFilter(String ext) {
			this.ext = "." + ext;
		}
		
		public boolean accept(File dir, String name){
			return name.endsWith(ext);
		}
	}
	
	public void processAdvancedTab() {
		
        if (chckbxEditInputs.isSelected()){		
        	switch (cbSourceOne.getSelectedIndex()) {
        		case 0: 
        			sourceOne = 0x01;
        			break;
        		case 1: 
        			sourceOne = 0x02;
        			break;
        	}
		
        	switch (cbSourceTwo.getSelectedIndex()) {
        		case 0: 
        			sourceTwo = 0x00;
        			break;
        		case 1: 
        			sourceTwo = 0x01;
        			break;
        		case 2: 
        			sourceTwo = 0x02;
        			break;
        	}
		
        	switch (cbGuitarIn.getSelectedIndex()) {
        		case 0: 
        			guitarIn = 0x00;
        			break;
        		case 1: 
        			guitarIn = 0x01;
        			break;
        		case 2: 
        			guitarIn = 0x02;
        			break;
        		case 3: 
        			guitarIn = 0x03;
        			break;
        		case 4: 
        			guitarIn = 0x04;
        			break;
        		case 5: 
        			guitarIn = 0x05;
        			break;
        		case 6: 
        			guitarIn = 0x06;
        			break;
        		case 7: 
        			guitarIn = 0x07;
        			break;
        		case 8: 
        			guitarIn = 0x08;
        			break;
        	}			   
        }
        
	}
	
	public boolean modifyPresetFiles(File listFile, String mode) throws Exception {
		
		RandomAccessFile raf = new RandomAccessFile(listFile, mode);
		raf.seek(0x000B);
		raf.write(0x28);
		raf.seek(0x000C);
		raf.write(0x01);
		raf.seek(0x000D);
		raf.write(0x06);
		raf.seek(0x0013);
		raf.write(0x03);
		raf.seek(0x0014);
		raf.write(0x02);
		raf.seek(0x0015);
		raf.write(0x02);
		raf.seek(0x0DFA);
		raf.write(guitarIn);
		raf.seek(0x1026);
		raf.write(sourceOne);
		raf.seek(0x1027);
		raf.write(sourceTwo);
		raf.close();
		return true;
	}
	
	public boolean modifyBundleFiles(File listFile, String mode) throws Exception {
		RandomAccessFile raf = new RandomAccessFile(listFile, mode);
		
		// Header
		raf.seek(0x00000B);
		raf.write(0x03);
		raf.seek(0x00000D);
		raf.write(0x01);
		raf.seek(0x000017);
		raf.write(0x28);
		raf.seek(0x000033);
		raf.write(0x03);
		raf.seek(0x000035);
		raf.write(0x01);
		raf.seek(0x00003F);
		raf.write(0x28);
		raf.seek(0x00006B);
		raf.write(0x28);
		raf.seek(0x000073);
		raf.write(0x03);
		raf.seek(0x000075);
		raf.write(0x01);
		
		// Content 1-8
		for (int j=0; j<8; j++) {
	        for (int i=0; i<64; i++) {
	    		raf.seek((0x000E5A + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(guitarIn);
	    		raf.seek((0x001086 + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(sourceOne);
	    		raf.seek((0x001087 + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(sourceTwo);
	    		raf.seek((0x001093 + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(0x28);
	    		raf.seek((0x00109B + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(0x03);
	    		raf.seek((0x00109D + (j * 0x40A38)) + (i * 0x1028));
	    		raf.write(0x01);
	        }
		}

        
        // Setlist 2-8
        for (int i=0; i<7; i++) {
        	raf.seek(0x040A6B + (i * 0x40A38));
        	raf.write(0x03);
        	raf.seek(0x040A6D + (i * 0x40A38));
        	raf.write(0x01);
        	raf.seek(0x040A77 + (i * 0x40A38));
        	raf.write(0x28);
        	raf.seek(0x040AA3 + (i * 0x40A38));
        	raf.write(0x28);
        	raf.seek(0x040AAB + (i * 0x40A38));
        	raf.write(0x03);
        	raf.seek(0x040AAD + (i * 0x40A38));
        	raf.write(0x01);
        }

        // Footer
        
		raf.close();
		return true;
	}
	
	public boolean modifySetlistFiles(File listFile, String mode) throws Exception {
		RandomAccessFile raf = new RandomAccessFile(listFile, mode);
		
		// Header
		raf.seek(0x00000B);
		raf.write(0x03);
		raf.seek(0x00000D);
		raf.write(0x01);
		raf.seek(0x000017);
		raf.write(0x28);
		raf.seek(0x000043);
		raf.write(0x28);
		raf.seek(0x00004B);
		raf.write(0x03);
		raf.seek(0x00004D);
		raf.write(0x01);
		
		// Content
	    	for (int i=0; i<64; i++) {
	    		raf.seek(0x000E32 + (i * 0x1028));
	    		raf.write(guitarIn);
	    		raf.seek(0x00105E + (i * 0x1028));
	    		raf.write(sourceOne);
	    		raf.seek(0x00105F + (i * 0x1028));
	    		raf.write(sourceTwo);
	    		raf.seek(0x00106B + (i * 0x1028));
	    		raf.write(0x28);
	    		raf.seek(0x001073 + (i * 0x1028));
	    		raf.write(0x03);
	    		raf.seek(0x001075 + (i * 0x1028));
	    		raf.write(0x01);
	        }

        // Footer
        
		raf.close();
		return true;
	}
	
	public boolean modifyPresetFiles300(File sourceFile, File targetFile, String patternTo, String mode) throws Exception {
				
		//Create basic Structure
		
		//System.out.println(listFile);
		//System.out.println(sourceFile);
		//System.out.println(targetFile);
		
		//double multiPoti = (int) 0x7FFF / (int) 0x3F80;
		float multiPoti = 0x7FFF;
		//double multiPoti = 0x7FFF / 0x3F80;
		//double multiPoti = 2.01569;
		
		int hexIn = 0;
		int hexOut = 0;
		
		boolean ampOn = false, hasPreamp = false, reverbPrePost = false, hasNoiseGate = false, hasWah = false;
		boolean amp2On = false, hasPreamp2 = false;
		
		boolean hasDualamp = false;
		
		int fxOffPre = 0x00;
		int fxOffPost = 0x02;
		int fxOnPre = 0x04;
		int fxOnPost = 0x06;
		
        byte[] h3eStructure = new byte[] {0x48,0x33,0x45,0x50,0x00,0x00,0x00,0x01,0x7D,0x01,0x00,0x25,
        		0x02,0x01,0x00,0x00,0x00,0x14,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x65,0x66,0x61,0x75,0x6C,
        		0x74,0x20,0x50,0x72,0x65,0x73,0x65,0x74,0x20,0x20,0x00,(byte) 0x80,0x00,0x00,0x00,0x00,0x40,
        		0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x1F,0x03,0x00,0x00,0x00,0x00,
        		0x7F,(byte) 0xFF,0x12,0x7B,0x00,0x00,0x7F,(byte) 0xFF,(byte) 0xE8,(byte) 0x90,0x0E,0x2F,0x00,0x00,0x00,0x00,0x00,
        		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0x00,0x01,0x04,0x07,0x01,
        		0x04,0x00,0x00,0x00,0x01,0x02,0x03,0x00,0x04,0x00,0x00,0x00,0x04,0x05,0x06,0x00,0x00,
        		0x00,0x00,0x00,0x07,0x08,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
        		0x00};
		
		HashMap<Integer,Integer> Amps = new HashMap<Integer,Integer>();
		Amps.put(0x05, 0x00);
		Amps.put(0x06, 0x10);
		Amps.put(0x08, 0x01);
		Amps.put(0x0E, 0x02);
		Amps.put(0x14, 0x03);
		Amps.put(0x01, 0x04);
		Amps.put(0x02, 0x11);
		Amps.put(0x03, 0x05);
		Amps.put(0x04, 0x12);
		Amps.put(0x12, 0x06);
		Amps.put(0x00, 0x07);
		Amps.put(0x10, 0x08);
		Amps.put(0x11, 0x09);
		Amps.put(0x09, 0x13);
		Amps.put(0x0A, 0x0A);
		Amps.put(0x55, 0x16);
		Amps.put(0x58, 0x17);
		Amps.put(0x0C, 0x14);
		Amps.put(0x0D, 0x0B);
		Amps.put(0x15, 0x0C);
		Amps.put(0x17, 0x0D);
		Amps.put(0x0B, 0x0E);		
		Amps.put(0x19, 0x0F);
		Amps.put(0x52, 0x15);
		Amps.put(0x5B, 0x1D);
		
		// Pre Models
		Amps.put(0x20, 0x00);
		Amps.put(0x21, 0x10);
		Amps.put(0x23, 0x01);
		Amps.put(0x29, 0x02);
		Amps.put(0x2F, 0x03);
		Amps.put(0x1C, 0x04);
		Amps.put(0x1D, 0x11);
		Amps.put(0x1E, 0x05);
		Amps.put(0x1F, 0x12);
		Amps.put(0x2D, 0x06);
		Amps.put(0x1B, 0x07);
		Amps.put(0x2B, 0x08);
		Amps.put(0x2C, 0x09);
		Amps.put(0x24, 0x13);
		Amps.put(0x25, 0x0A);
		Amps.put(0x56, 0x16);
		Amps.put(0x59, 0x17);
		Amps.put(0x27, 0x14);
		Amps.put(0x28, 0x0B);
		Amps.put(0x30, 0x0C);
		Amps.put(0x32, 0x0D);
		Amps.put(0x26, 0x0E);
		Amps.put(0x34, 0x0F);
		Amps.put(0x53, 0x15);
		Amps.put(0x5C, 0x19);
		
		HashMap<Integer,Integer> PreAmps = new HashMap<Integer,Integer>();
		
		// Pre Models
		PreAmps.put(0x20, 0x00);
		PreAmps.put(0x21, 0x10);
		PreAmps.put(0x23, 0x01);
		PreAmps.put(0x29, 0x02);
		PreAmps.put(0x2F, 0x03);
		PreAmps.put(0x1C, 0x04);
		PreAmps.put(0x1D, 0x11);
		PreAmps.put(0x1E, 0x05);
		PreAmps.put(0x1F, 0x12);
		PreAmps.put(0x2D, 0x06);
		PreAmps.put(0x1B, 0x07);
		PreAmps.put(0x2B, 0x08);
		PreAmps.put(0x2C, 0x09);
		PreAmps.put(0x24, 0x13);
		PreAmps.put(0x25, 0x0A);
		PreAmps.put(0x56, 0x16);
		PreAmps.put(0x59, 0x17);
		PreAmps.put(0x27, 0x14);
		PreAmps.put(0x28, 0x0B);
		PreAmps.put(0x30, 0x0C);
		PreAmps.put(0x32, 0x0D);
		PreAmps.put(0x26, 0x0E);
		PreAmps.put(0x34, 0x0F);
		PreAmps.put(0x53, 0x15);
		PreAmps.put(0x5C, 0x19);
				
		HashMap<Integer,Integer> Cabs = new HashMap<Integer, Integer>();
		Cabs.put(0x00, 0x08);
		Cabs.put(0x01, 0x03);
		Cabs.put(0x02, 0x07);
		Cabs.put(0x03, 0x06);
		Cabs.put(0x04, 0x04);
		Cabs.put(0x05, 0x09);
		Cabs.put(0x06, 0x01);
		Cabs.put(0x08, 0x0A);
		Cabs.put(0x09, 0x05);
		Cabs.put(0x0A, 0x0E);
		Cabs.put(0x0B, 0x10);
		Cabs.put(0x0C, 0x02);
		Cabs.put(0x0E, 0x0B);
		Cabs.put(0x11, 0x0C);
		Cabs.put(0x10, 0x0F);
		Cabs.put(0x0F, 0x0D);
		Cabs.put(0x12, 0x11);
		
		// Effects
		
		// Dynamics
		HashMap<Integer,Integer> Dyn1 = new HashMap<Integer, Integer>();
		Dyn1.put(0x12, 0x12);
		Dyn1.put(0x0B, 0x13);
		Dyn1.put(0x0C, 0x14);
		Dyn1.put(0x0F, 0x16);
		Dyn1.put(0x13, 0x5F);
		
		// Effect mapped (not available on hd300)
		Dyn1.put(0x0E, 0x13); // Tube Comp -> Red Comp
		Dyn1.put(0x0D, 0x14); // Blue Comp Treb -> Blue Comp
		Dyn1.put(0x10, 0x16); // Vetta Juice -> Vetta Comp
				
		// Distortion
		HashMap<Integer,Integer> Dist1 = new HashMap<Integer, Integer>();
		Dist1.put(0x0E, 0x01);
		Dist1.put(0x0D, 0x0B);
		Dist1.put(0x0B, 0x0C);
		Dist1.put(0x16, 0x0D);
		Dist1.put(0x18, 0x0E);
		Dist1.put(0x10, 0x0F);
		Dist1.put(0x13, 0x10);
		Dist1.put(0x12, 0x11);		
		Dist1.put(0x0F, 0x18);
		Dist1.put(0x0C, 0x19);
		Dist1.put(0x0A, 0x1A);
		Dist1.put(0x14, 0x1B);
		Dist1.put(0x11, 0x1D);
		Dist1.put(0x17, 0x1E);
		
		// Effect mapped (not available on hd300)
		Dist1.put(0x15, 0x1A); // Buzz Saw -> Jet Fuzz
		
		// Modulator
		HashMap<Integer,Integer> Mod1 = new HashMap<Integer, Integer>();
		Mod1.put(0x2E, 0x2A);
		Mod1.put(0x2B, 0x2B);
		Mod1.put(0x42, 0x2C);
		Mod1.put(0x26, 0x2D);
		
		// Effect mapped (not available on hd300
		Mod1.put(0x27, 0x2D); // Rotary Dum & Horn -> Rotary Dum
		
		HashMap<Integer,Integer> Mod2 = new HashMap<Integer, Integer>();
		Mod2.put(0x2A, 0x04);
		Mod2.put(0x28, 0x36);
		Mod2.put(0x25, 0x37);
		Mod2.put(0x22, 0x38);
		Mod2.put(0x23, 0x39);
		Mod2.put(0x40, 0x3A);
		Mod2.put(0x24, 0x3B);
		Mod2.put(0x45, 0x3C);
		Mod2.put(0x2D, 0x3D);
		Mod2.put(0x20, 0x06);
		Mod2.put(0x21, 0x42);
		Mod2.put(0x43, 0x43);
		Mod2.put(0x2F, 0x44);
		
		// Effect mapped (not available on hd300)
		Mod2.put(0x2C, 0x04); // Tri Chorus -> Analog Chorus
		Mod2.put(0x29, 0x36); // Jet Flanger -> Analog Flanger
		Mod2.put(0x47, 0x36); // AC Flanger -> Analog Flanger
		Mod2.put(0x49, 0x36); // 80A Flanger -> Analog Flanger

		// Filter
		HashMap<Integer,Integer> Filter1 = new HashMap<Integer, Integer>();
		Filter1.put(0x10, 0x27);
		Filter1.put(0x0F, 0x28);
		Filter1.put(0x14, 0x29);
		Filter1.put(0x1C, 0x31);
		Filter1.put(0x19, 0x32);
		Filter1.put(0x1A, 0x33);
		Filter1.put(0x1E, 0x35);
		
		// Effect mapped (not available on hd300)
		Filter1.put(0x1B, 0x31); // Attack Synth -> Synth String
	
		HashMap<Integer,Integer> Filter2 = new HashMap<Integer, Integer>();
		Filter2.put(0x11, 0x05);
		Filter2.put(0x15, 0x3E);
		Filter2.put(0x16, 0x3F);
		Filter2.put(0x14, 0x40);
		Filter2.put(0x1D, 0x41);
		
		// Effect mapped (not available on hd300)
		Filter2.put(0x26, 0x05); // Vocodoer -> Seeker
		Filter2.put(0x13, 0x3E); // Slow Filter -> Throbber
		Filter2.put(0x17, 0x3F); // Comet Trails -> Spin Cycle
		Filter2.put(0x18, 0x3F); // Octisynth -> Spin Cycle
		
		// Pitcher
		HashMap<Integer,Integer> Pitch1 = new HashMap<Integer, Integer>();
		Pitch1.put(0x03, 0x03);
		Pitch1.put(0x02, 0x2F);
		Pitch1.put(0x04, 0x34);
		
		// Equalizer + Pre
		HashMap<Integer,Integer> Eq1 = new HashMap<Integer, Integer>();
		Eq1.put(0x0B, 0x23);
		Eq1.put(0x0C, 0x24);
		Eq1.put(0x0E, 0x5E);
		
		// Effect mapped (not available on hd300)
		Eq1.put(0x09, 0x23); // Graphic EQ -> Parametic EQ
		Eq1.put(0x0A, 0x24); // Studio EQ -> 4 Band Shift EQ
		Eq1.put(0x0D, 0x24); // Mid Focus EQ -> 4 Band Shift EQ
		
		// Delay
		HashMap<Integer,Integer> Delay3 = new HashMap<Integer, Integer>();		
		Delay3.put(0x11, 0x07);
		Delay3.put(0x12, 0x45);
		Delay3.put(0x14, 0x46);
		Delay3.put(0x15, 0x47);
		Delay3.put(0x30, 0x48);
		Delay3.put(0x31, 0x49);
		Delay3.put(0x1D, 0x4A);
		Delay3.put(0x13, 0x4B);
		
		Delay3.put(0x20, 0x4C);
		Delay3.put(0x22, 0x4D);
		Delay3.put(0x2C, 0x08);
		Delay3.put(0x2D, 0x4E);
		Delay3.put(0x2A, 0x4F);
		Delay3.put(0x2B, 0x50);
		Delay3.put(0x23, 0x09);
		Delay3.put(0x2E, 0x52);
		Delay3.put(0x2F, 0x53);
		Delay3.put(0x21, 0x54);
		
		// Effect mapped (not available on hd300)
		Delay3.put(0x1A, 0x11); // Multi-Head Delay -> Digital Delay!?
		
		// Reverb
		HashMap<Integer,Integer> Reverb1 = new HashMap<Integer, Integer>();
		Reverb1.put(0x1D, 0x02);
		
		// Effect mapped (not available on hd300)
		Reverb1.put(0x1C, 0x02); // '63 Spring -> Spring
		Reverb1.put(0x27, 0x02); // Particle Verb -> Spring

		HashMap<Integer,Integer> ReverbSlot = new HashMap<Integer, Integer>();
		ReverbSlot.put(0x1E, 0x0A);
		ReverbSlot.put(0x1F, 0x55);
		ReverbSlot.put(0x20, 0x56);
		ReverbSlot.put(0x21, 0x57);
		ReverbSlot.put(0x24, 0x58);
		ReverbSlot.put(0x23, 0x5A);
		ReverbSlot.put(0x25, 0x5B);
		ReverbSlot.put(0x26, 0x5C);
		
		// Effect mapped (not available on hd300)
		ReverbSlot.put(0x22, 0x58); // Ducking -> Cave
		
		// Wah
		HashMap<Integer,Integer> WahSlot = new HashMap<Integer, Integer>();
		WahSlot.put(0x0B, 0x00);
		WahSlot.put(0x0C, 0x01);
		WahSlot.put(0x0E, 0x02);
		WahSlot.put(0x0D, 0x03);
		WahSlot.put(0x11, 0x04);
		WahSlot.put(0x12, 0x05);
		
		// Effect mapped (not available on hd300)
		WahSlot.put(0x10, 0x04); // Throaty -> Conductor
		WahSlot.put(0x0F, 0x02); // Chrome Custom -> Chrome
		
		List<HashMap<Integer, Integer>> listFx1 = new ArrayList<HashMap<Integer, Integer>>();
		listFx1.add(Dyn1);
		listFx1.add(Dist1);
		listFx1.add(Mod1);
		listFx1.add(Filter1);
		listFx1.add(Pitch1);
		listFx1.add(Eq1);
		listFx1.add(Reverb1);
		
		RandomAccessFile rafSource = new RandomAccessFile(sourceFile, mode);
		RandomAccessFile rafTarget = new RandomAccessFile(targetFile, mode);
		
		// Begin
		
		// Write Default Template
		
		rafTarget.write(h3eStructure);
		
		// Set Preset Name
		
		byte[] presetName = new byte[16];
		rafSource.seek(0x28);
		rafSource.readFully(presetName);
		rafTarget.seek(0x28);
		rafTarget.write(presetName);
		
		// Check if Amp is On
		rafSource.seek(0x58);
		hexIn = rafSource.read();
		if(hexIn == 0x01) {
			ampOn = true;
		}
		
		// Turn first Amp On
				
		// rafSource.seek(0x58);
		// hexIn = rafSource.read();
		// rafTarget.seek(0x39);
		// if(hexIn == 0x01) {
		// 	rafTarget.write(0x80);
		// } else if (hexIn == 0x00) {
		// 	rafTarget.write(0x00);
		// }
		
		// Seek and Write for first Amp Model
		
		rafSource.seek(0x53);
		hexIn = rafSource.read();
		rafTarget.seek(0x3B);
		rafTarget.write((Integer) Amps.get(hexIn));
		
		// Check for PreAmp
		rafSource.seek(0x53);
		int checkPreamp = rafSource.read();
		if(PreAmps.containsKey(checkPreamp)) {
			rafTarget.seek(0x4D);
			rafTarget.write(0x01);
			hasPreamp = true;
		} else {
			rafTarget.seek(0x4D);
			rafTarget.write(0x00);
			hasPreamp = false;
		}
		
		// Turn first Cab On
		
		rafSource.seek(0x25B);
		hexIn = rafSource.read();
		if(hexIn == 0x00) {
			rafTarget.seek(0x3D);
			rafTarget.write(0x12);
		}
		
		// Seek and Write for first Cab Model
		
		rafSource.seek(0x253);
		hexIn = rafSource.read();
		rafTarget.seek(0x3D);
		rafTarget.write((Integer) Cabs.get(hexIn));
		
		// Convert (From 2 Bytes to 3 Bytes accuracy) Amp Potis and write them down
		// Drive		
		poti(rafSource, rafTarget, 0x64, 0x3E);
		
		// Bass
		poti(rafSource, rafTarget, 0x78, 0x40);

		// Mid
		poti(rafSource, rafTarget, 0x8C, 0x42);

		// Treble
		poti(rafSource, rafTarget, 0xA0, 0x44);

		// Pres
		poti(rafSource, rafTarget, 0xB4, 0x48);

		// CH. Vol
		poti(rafSource, rafTarget, 0xC8, 0x46);

		// E.R.
		poti(rafSource, rafTarget, 0xD74, 0x4E);
		
		

		// BYP Vol.
		poti(rafSource, rafTarget, 0xDA4, 0x50);
		
		

		// Master
		poti(rafSource, rafTarget, 0x12C, 0x64);

		// Sag
		poti(rafSource, rafTarget, 0xF0, 0x5E);

		// Hum
		poti(rafSource, rafTarget, 0xDC, 0x5C);

		// Bias
		poti(rafSource, rafTarget, 0x104, 0x60);
		
		// Bias X
		poti(rafSource, rafTarget, 0x118, 0x62);
		
		// Cab Parameter (Not Available on POD HD 300?)

		// Low Cut
		//poti(rafSource, rafTarget, 0x264, 0x);
		
		// Res Level
		//poti(rafSource, rafTarget, 0x278, 0x);

		// Thump
		//poti(rafSource, rafTarget, 0x28C, 0x);

		// Decay
		//poti(rafSource, rafTarget, 0x2A0, 0x);
		
		// Microphone
		
		rafSource.seek(0x1020);
		hexIn = rafSource.read();
		rafTarget.seek(0x4C);
		rafTarget.write(hexIn);
		
		// Effects
		
		// FX1
		
		// Check which effects are available
				
		int effectType, effectModell;

		// holds Number of Effects in Slots
		int fx1 = 0, fx2 = 0, fx3 = 0, reverbSlot = 0, Wah = 0; 
		
		
		// Check for Number of Effects in Slots
		
		for (int j = 0x0; j<0x800; j += 0x100) {
			
			rafSource.seek(0x451 + j);
			effectType = rafSource.read();
		
			switch (effectType) {
			case 0x00:
				// Dyn Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				
				// Check for Noise Gate
				
				// Set Effect
				if (Dyn1.containsKey(effectModell)) {
					
					fx1 += 1;
				}		
				break;
			case 0x05:
				// Dist Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Dist1.containsKey(effectModell)) {
					
					fx1 += 1;
				}		
				break;
			case 0x03:
				// Mod Effect
				
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Mod1.containsKey(effectModell)) {
					
					fx1 += 1;
					
				// Check for 2nd Slot
									
				// Check for Type of Effect
				} else if (Mod2.containsKey(effectModell)) {
					
					fx2 += 1;
				}			
				break;
			case 0x0A:
				// Filter Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Filter1.containsKey(effectModell)) {
					
					fx1 += 1;
					
				// Check for 2nd Slot
					
				// Check for Type of Effect
				} else if (Filter2.containsKey(effectModell)) {	
					
					fx2 += 1;
				}	
				break;
			case 0x09:
				// Pitch Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Pitch1.containsKey(effectModell)) {

					
					fx1 += 1;
				}	
				break;
			case 0x0C:
				//  EQ+Pre Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Eq1.containsKey(effectModell)) {
					
					fx1 += 1;
				}	
				break;
			case 0x02:
				// Delay Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Delay3.containsKey(effectModell)) {
					
					fx3 += 1;
				}	
				break;
			case 0x04:
				// Reverb Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (Reverb1.containsKey(effectModell)) {
					
					fx1 += 1;
					
				// Check for ReverbSlot
					
				// Check for Type of Effect
				} else if (ReverbSlot.containsKey(effectModell)) {
					
					reverbSlot += 1;
				}
				break;
			case 0x07:
				//  VolPan Effect
				break;
			case 0x06:
				// Wah Effect
				
				// Check for Type of Effect
				rafSource.seek(0x453 + j);
				effectModell = rafSource.read();
				if (WahSlot.containsKey(effectModell)) {
					
					Wah += 1;
				}
				break;
			case 0x08:
				// FXLoop Effect
				break;
			}
		}
		
		rafTarget.close();
		
		int v2 = 0, w2 = 0, x2 = 0, y2 = 0, z2 = 0;
		
		if (fx1 != 0) v2++;
		if (fx2 != 0) w2++;
		if (fx3 != 0) x2++;
		if (reverbSlot != 0) y2++;
		if (Wah != 0) z2++;
		
		for (int v=v2; v<=fx1; v++) {
			for (int w=w2; w<=fx2; w++) {
				for (int x=x2; x<=fx3; x++) {
					for (int y=y2; y<=reverbSlot; y++) {
						for (int z=z2; z<=Wah; z++) {
							
						    File fileLoop = new File(dir.getAbsolutePath()  + "/" + fileBaseName(targetFile) +
						    Integer.toString(v) + Integer.toString(w) + Integer.toString(x) + 
						    Integer.toString(y) + Integer.toString(z) + "." + getFileExtension(targetFile.getName()));
						    //System.out.println(fileLoop.getAbsolutePath());
							Files.copy(targetFile.toPath(), fileLoop.toPath());
							
							RandomAccessFile rafTargetLoop = new RandomAccessFile(fileLoop, mode);
							
							int fx1a = 1, fx2a = 1, fx3a = 1, reverbSlota = 1, Waha = 1;
							
							final List<Integer> preEffects = Arrays.asList(0x00, 0x01, 0x02);
							final List<Integer> postEffects = Arrays.asList(0x03, 0x04, 0x05);
							
							for (int j = 0x0; j<0x800; j += 0x100) {
								
								//System.out.println(Integer.toHexString(0x451 + j));
								
								rafSource.seek(0x451 + j);
								effectType = rafSource.read();
							
								switch (effectType) {
								case 0x00:
									// Dyn Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									
									// Check for Noise Gate
									
									if (effectModell == 0x11) {
										// Found NoiseGate
										
										// 1. Poti - Tresh
										potiDecibel(rafSource, rafTargetLoop, 0x464 + j, 0x58);
										
										// 2. Poti - Decay
										poti(rafSource, rafTargetLoop, 0x478 + j, 0x5A);
										
										hasNoiseGate = true;
									}
									
									// Set Effect
									if (Dyn1.containsKey(effectModell)) {
										if (fx1a == v) {
											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Dyn1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;											

									}		
									break;
								case 0x05:
									// Dist Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Dist1.containsKey(effectModell)) {
										if (fx1a == v) {

											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Dist1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a++;

									}		
									break;
								case 0x03:
									// Mod Effect
									
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Mod1.containsKey(effectModell)) {
										if (fx1a == v) {

											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Mod1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;
										
									// Check for 2nd Slot
										
										
									// Check for Type of Effect
									} else if (Mod2.containsKey(effectModell)) {
										if (fx2a == w) {

											rafTargetLoop.seek(0x7D);
											rafTargetLoop.write((Integer) Mod2.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x7D);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6F);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x96);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x98);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x9A);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x9C);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0xA0);
											
										}
										fx2a += 1;

									}			
									break;
								case 0x0A:
									// Filter Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Filter1.containsKey(effectModell)) {
										if (fx1a == v) {

											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Filter1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);				
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;
										
									// Check for 2nd Slot
										
									// Check for Type of Effect
									} else if (Filter2.containsKey(effectModell)) {
										if (fx2a == w) {
											rafTargetLoop.seek(0x7D);
											rafTargetLoop.write((Integer) Filter2.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x7D);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6F);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x7A);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x96);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x98);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x9A);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x9C);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0xA0);
											
										}
										fx2a += 1;
										
									}	
									break;
								case 0x09:
									// Pitch Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Pitch1.containsKey(effectModell)) {
										if (fx1a == v) {
											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Pitch1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);	
													
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;

									}	
									break;
								case 0x0C:
									//  EQ+Pre Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Eq1.containsKey(effectModell)) {
										if (fx1a == v) {
											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Eq1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);
												
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;

									}	
									break;
								case 0x02:
									// Delay Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Delay3.containsKey(effectModell)) {
										if (fx3a == x) {
											rafTargetLoop.seek(0x85);
											rafTargetLoop.write((Integer) Delay3.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x85);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x70);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x82);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x82);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x82);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x82);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0xA2);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0xA4);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0xA6);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0xA8);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0xAA);
											
										}
										fx3a += 1;

									}	
									break;
								case 0x04:
									// Reverb Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (Reverb1.containsKey(effectModell)) {										
										if (fx1a == v) {

											rafTargetLoop.seek(0x75);
											rafTargetLoop.write((Integer) Reverb1.get(effectModell));
											
											// Write again at different Place
											rafTargetLoop.seek(0x75);
											hexIn = rafTargetLoop.read();
											rafTargetLoop.seek(0x6E);
											rafTargetLoop.write(hexIn);	
											
											// See if Effect is Online and Set it On
											rafSource.seek(0x45B + j);
											int effectOn = rafSource.read();
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (effectOn == 0x01 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPre);
											} else if (effectOn == 0x01 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOnPost);
											} else if (effectOn == 0x00 && preEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPre);
											} else if (effectOn == 0x00 && postEffects.contains(effectPrePost)) {
												rafTargetLoop.seek(0x72);
												rafTargetLoop.write(fxOffPost);
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0x8C);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0x8E);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0x90);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0x92);
											
											// 5. Poti
											poti(rafSource, rafTargetLoop, 0x4B4 + j, 0x94);
											
										}
										fx1a += 1;
										
									// Check for ReverbSlot
										
									// Check for Type of Effect
									} else if (ReverbSlot.containsKey(effectModell)) {
										if (reverbSlota == y) {
											rafTargetLoop.seek(0x6C);
											rafTargetLoop.write((Integer) ReverbSlot.get(effectModell));
											
											// Set Pre/Post since it is always on
											rafSource.seek(0x455 + j);
											int effectPrePost = rafSource.read();
											if (preEffects.contains(effectPrePost)) {
												reverbPrePost = false; // Set false if Pre
											} else if (postEffects.contains(effectPrePost)) {
												reverbPrePost = true; // Set true if Post
											}
											
											// Set Potis
											
											// 1. Poti
											poti(rafSource, rafTargetLoop, 0x464 + j, 0xB0);
											
											// 2. Poti
											poti(rafSource, rafTargetLoop, 0x478 + j, 0xB2);
							
											// 3. Poti
											poti(rafSource, rafTargetLoop, 0x48C + j, 0xB4);
							
											// 4. Poti
											poti(rafSource, rafTargetLoop, 0x4A0 + j, 0xB8);
																						
										}
										reverbSlota += 1;

									}
									break;
								case 0x07:
									//  VolPan Effect
									break;
								case 0x06:
									// Wah Effect
									
									// Check for Type of Effect
									rafSource.seek(0x453 + j);
									effectModell = rafSource.read();
									if (WahSlot.containsKey(effectModell)) {
										if (Waha == z) {
											rafTargetLoop.seek(0x6D);
											rafTargetLoop.write((Integer) WahSlot.get(effectModell));
											
											// Set Potis
											
											// 1. Poti
											potiByte(rafSource, rafTargetLoop, 0x464 + j, 0xBA);
											
											hasWah = true;
											
										}
										Waha += 1;
	
									}
									break;
								case 0x08:
									// FXLoop Effect
									break;
								}
							}
													
							// Setup Amp, NoiseGate, Wah and Reverb Byte:
								
							rafTargetLoop.seek(0x39);
							if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
								rafTargetLoop.write(0x80);
							} else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
								rafTargetLoop.write(0x88);
							} else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
								rafTargetLoop.write(0x81);
							} else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
								rafTargetLoop.write(0x89);
							} else if (ampOn && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
								rafTargetLoop.write(0xC0);
							} else if (ampOn && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
								rafTargetLoop.write(0xC8);
							} else if (ampOn && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
								rafTargetLoop.write(0xC1);
							} else if (ampOn && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
								rafTargetLoop.write(0xC9);
								
							} else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
								rafTargetLoop.write(0x00);
							} else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
								rafTargetLoop.write(0x08);
							} else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
								rafTargetLoop.write(0x01);
							} else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
								rafTargetLoop.write(0x09);
							} else if (ampOn == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
								rafTargetLoop.write(0x40);
							} else if (ampOn == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
								rafTargetLoop.write(0x48);
							} else if (ampOn == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
								rafTargetLoop.write(0x41);
							} else if (ampOn == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
								rafTargetLoop.write(0x49);
							}
							
							rafTargetLoop.close();

							// Check for Dualamp Preset and MultiSlot Assignment
							
							// Check if 2nd Amp set (either off or on, but defined)
							rafSource.seek(0x15B);
							hexIn = rafSource.read();
							if(hexIn == 0x01) {
								
								// Found 2nd Amp, do something!
								hasDualamp = true;
								
							}
																
							if (hasDualamp) {
								//System.out.println("dualamp!");
								
							    File newFile = new File(dir.getAbsolutePath()  + "/" + 
							    fileBaseName(fileLoop) + "2ndAmp." +  getFileExtension(fileLoop.getName()));
							    //System.out.println(newFile.getAbsolutePath());
								Files.copy(fileLoop.toPath(), newFile.toPath());
								
								//RandomAccessFile rafSource = new RandomAccessFile(sourceFile, mode);
								RandomAccessFile rafTargetLoop2 = new RandomAccessFile(newFile, mode);
								
								// Check if second Amp is On
								rafSource.seek(0x158);
								hexIn = rafSource.read();
								if(hexIn == 0x01) {
									amp2On = true;
								}
								
								// Turn second Amp On
										
								// rafSource.seek(0x58);
								// hexIn = rafSource.read();
								// rafTargetLoop.seek(0x39);
								// if(hexIn == 0x01) {
								// 	rafTargetLoop.write(0x80);
								// } else if (hexIn == 0x00) {
								// 	rafTargetLoop.write(0x00);
								// }
								
								// Seek and Write for second Amp Model
								
								rafSource.seek(0x153);
								hexIn = rafSource.read();
								rafTargetLoop2.seek(0x3B);
								rafTargetLoop2.write((Integer) Amps.get(hexIn));
								
								// Check for PreAmp
								rafSource.seek(0x153);
								int checkPreamp2 = rafSource.read();
								if(PreAmps.containsKey(checkPreamp2)) {
									rafTargetLoop2.seek(0x4D);
									rafTargetLoop2.write(0x01);
									hasPreamp2 = true;
								} else {
									rafTargetLoop2.seek(0x4D);
									rafTargetLoop2.write(0x00);
									hasPreamp2 = false;
								}
								
								// Turn second Cab On
								
								rafSource.seek(0x35B);
								hexIn = rafSource.read();
								if(hexIn == 0x00) {
									rafTargetLoop2.seek(0x3D);
									rafTargetLoop2.write(0x12);
								}
								
								// Seek and Write for second Cab Model
								
								rafSource.seek(0x353);
								hexIn = rafSource.read();
								rafTargetLoop2.seek(0x3D);
								rafTargetLoop2.write((Integer) Cabs.get(hexIn));
								
								// Convert (From 2 Bytes to 3 Bytes accuracy) Amp Potis and write them down
								// Drive		
								poti(rafSource, rafTargetLoop2, 0x164, 0x3E);
								
								// Bass
								poti(rafSource, rafTargetLoop2, 0x178, 0x40);

								// Mid
								poti(rafSource, rafTargetLoop2, 0x18C, 0x42);

								// Treble
								poti(rafSource, rafTargetLoop2, 0x1A0, 0x44);

								// Pres
								poti(rafSource, rafTargetLoop2, 0x1B4, 0x48);

								// CH. Vol
								poti(rafSource, rafTargetLoop2, 0x1C8, 0x46);

								// E.R.
								poti(rafSource, rafTargetLoop2, 0xD7C, 0x4E);
								
								

								// BYP Vol.
								poti(rafSource, rafTargetLoop2, 0xDA8, 0x50);
								
								

								// Master
								poti(rafSource, rafTargetLoop2, 0x22C, 0x64);

								// Sag
								poti(rafSource, rafTargetLoop2, 0x2F0, 0x5E);

								// Hum
								poti(rafSource, rafTargetLoop2, 0x2DC, 0x5C);

								// Bias
								poti(rafSource, rafTargetLoop2, 0x204, 0x60);
								
								// Bias X
								poti(rafSource, rafTargetLoop2, 0x218, 0x62);
								
								// Cab Parameter (Not Available on POD HD 300?)

								// Low Cut
								//poti(rafSource, rafTargetLoop2, 0x364, 0x);
								
								// Res Level
								//poti(rafSource, rafTargetLoop2, 0x378, 0x);

								// Thump
								//poti(rafSource, rafTargetLoop2, 0x38C, 0x);

								// Decay
								//poti(rafSource, rafTargetLoop2, 0x3A0, 0x);
								
								// Second Microphone
								
								rafSource.seek(0x1021);
								hexIn = rafSource.read();
								rafTargetLoop2.seek(0x4C);
								rafTargetLoop2.write(hexIn);
								
								rafTargetLoop2.seek(0x39);
								if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
									rafTargetLoop2.write(0x80);
								} else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
									rafTargetLoop2.write(0x88);
								} else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
									rafTargetLoop2.write(0x81);
								} else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
									rafTargetLoop2.write(0x89);
								} else if (amp2On && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
									rafTargetLoop2.write(0xC0);
								} else if (amp2On && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
									rafTargetLoop2.write(0xC8);
								} else if (amp2On && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
									rafTargetLoop2.write(0xC1);
								} else if (amp2On && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
									rafTargetLoop2.write(0xC9);
									
								} else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == false) {
									rafTargetLoop2.write(0x00);
								} else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == false) {
									rafTargetLoop2.write(0x08);
								} else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == false) {
									rafTargetLoop2.write(0x01);
								} else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == false) {
									rafTargetLoop2.write(0x09);
								} else if (amp2On == false && reverbPrePost == false && hasNoiseGate == false && hasWah == true) {
									rafTargetLoop2.write(0x40);
								} else if (amp2On == false && reverbPrePost == true && hasNoiseGate == false && hasWah == true) {
									rafTargetLoop2.write(0x48);
								} else if (amp2On == false && reverbPrePost == false && hasNoiseGate == true && hasWah == true) {
									rafTargetLoop2.write(0x41);
								} else if (amp2On == false && reverbPrePost == true && hasNoiseGate == true && hasWah == true) {
									rafTargetLoop2.write(0x49);
								}
								
								rafTargetLoop2.close();


							}
							
						}
					}
				}
			}
		}

		rafSource.close();
		
		targetFile.delete();
		
		return true;
	}
	
	public boolean poti(RandomAccessFile rafSource, RandomAccessFile rafTarget, int sourcePosition, int targetPosition) throws IOException {
		
		float multiPoti = 0x7FFF;
		float floatDone, floatIn = 0.0f;
		int intConverted, hexOut1, hexOut2;

		rafSource.seek(sourcePosition);
		floatIn = rafSource.readFloat();
		floatDone = (floatIn * multiPoti);
		intConverted = Math.round(floatDone);
		hexOut1 = (intConverted & 0xFF);
		hexOut2 = ((intConverted >> 8) & 0xFF);
		rafTarget.seek(targetPosition);
		rafTarget.write(hexOut2);
		rafTarget.write(hexOut1);
		return true;
		
	}
	
	public boolean potiDecibel(RandomAccessFile rafSource, RandomAccessFile rafTarget, int sourcePosition, int targetPosition) throws IOException {
		
		float floatDone, floatIn = 0.0f;
		int intConverted, hexOut1, hexOut2;

		rafSource.seek(sourcePosition);
		floatIn = rafSource.readFloat();	
	    floatDone = 0x10000 - (0x25E8 * (floatIn));    	
		intConverted = Math.round(floatDone);
		hexOut1 = (intConverted & 0xFF);
		hexOut2 = ((intConverted >> 8) & 0xFF);
		rafTarget.seek(targetPosition);
		rafTarget.write(hexOut2);
		rafTarget.write(hexOut1);
		return true;
		
	}
	
	public boolean potiReverse(RandomAccessFile rafSource, RandomAccessFile rafTarget, int sourcePosition, int targetPosition) throws IOException {
		
		float multiPoti = 0x7FFF;
		float floatDone, floatDone2, floatIn = 0.0f;
		int intConverted, hexOut1, hexOut2;

		rafSource.seek(sourcePosition);
		floatIn = rafSource.readFloat();
		floatDone2 = (floatIn * multiPoti);
		floatDone = (floatDone2 - 0x7FFF);
		intConverted = Math.round(floatDone);
		hexOut1 = (intConverted & 0xFF);
		hexOut2 = ((intConverted >> 8) & 0xFF);
		rafTarget.seek(targetPosition);
		rafTarget.write(hexOut2);
		rafTarget.write(hexOut1);
		return true;
		
	}
	
	public boolean potiByte(RandomAccessFile rafSource, RandomAccessFile rafTarget, int sourcePosition, int targetPosition) throws IOException {
		
		float floatIn = 0.0f;
		byte byteDone;
		rafSource.seek(sourcePosition);
		floatIn = rafSource.readFloat();
		byteDone = (byte) (floatIn * 255);
		rafTarget.seek(targetPosition);
		rafTarget.write(byteDone);
		return true;
		
	}
	
	public boolean modifyBundleFiles300(File sourceFile, File targetFile, String mode) throws Exception {
		
		RandomAccessFile raf = new RandomAccessFile(sourceFile, mode);
		raf.close();
		return true;
	}
	
	public boolean modifySetlistFiles300(File sourceFile, File targetFile, String mode) throws Exception {
		
		RandomAccessFile raf = new RandomAccessFile(sourceFile, mode);
		raf.close();
		return true;
	}
   
   public void copyFiles(String pressedFrom) {
	   boolean backupDirCreated = false;
	   
	   if(pressedFrom.equals("Desktop")) {
		   if(chckbxBackup.isSelected()){
			   File backupDir = new File(dir.getAbsolutePath() + "/backup");
			   try {
				   backupDirCreated = backupDir.mkdir();
			   } catch (SecurityException Se) {
				   System.out.println("Error while creating directory in Java:" + Se);
			   }
			   try {
				   for (int i = 0; i < lPatchCheckboxes.size(); i++) {
					    if (lPatchCheckboxes.get(i).isSelected()) {
				            File sourceFiles[] = dir.listFiles(new extFileFilter(lFileExtension.get(i)));
				            
				            for (int j=0; j<sourceFiles.length; j++) {
				            		Files.copy(Paths.get(sourceFiles[j].getAbsolutePath()), Paths.get(backupDir + "/" + sourceFiles[j].getName()));
				            		}
				        }
				   }
			   } catch (IOException e) {
				   e.printStackTrace();
			   }
		   }
		   
	   } else if(pressedFrom.equals("300")) {
		   if(chckbx300Backup.isSelected()){
			   File backupDir = new File(dir.getAbsolutePath() + "/backup");
			   try {
				   backupDirCreated = backupDir.mkdir();
			   } catch (SecurityException Se) {
				   System.out.println("Error while creating directory in Java:" + Se);
			   }
			   try {
				   for (int i = 0; i < lPatchCheckboxes300.size(); i++) {
					    if (lPatchCheckboxes300.get(i).isSelected()) {
				            File sourceFiles[] = dir.listFiles(new extFileFilter(lFileExtension300.get(i)));
				            
				            for (int j=0; j<sourceFiles.length; j++) {
				            	try {
				            		Files.copy(Paths.get(sourceFiles[j].getAbsolutePath()), Paths.get(backupDir + "/" + sourceFiles[j].getName()));
				 			   	} catch (IOException e) {
								   e.printStackTrace();
				 			   	}
				            }
					    }
			       }
				   for (int i = 0; i < lPatchCheckboxes400.size(); i++) {
					    if (lPatchCheckboxes400.get(i).isSelected()) {
				            File sourceFiles[] = dir.listFiles(new extFileFilter(lFileExtension400.get(i)));
				            
				            for (int j=0; j<sourceFiles.length; j++) {
				            		Files.copy(Paths.get(sourceFiles[j].getAbsolutePath()), Paths.get(backupDir + "/" + sourceFiles[j].getName()));
				            }
				        }
				   }
			   } catch (IOException e) {
				   e.printStackTrace();
			   }
			   }   
	   }
   }
   
   public void renameFile() {
	   
	   for (int i = 0; i < lRenameCheckboxes.size(); i++) {
		    if (lRenameCheckboxes.get(i).isSelected()) {
		        String fileListString[] = dir.list(new extNameFilter(lFileExtension.get(i)));
	       		if (fileListString != null) {
	       			for (int j=0; j<fileListString.length; j++) {
	       				try {
	                	   renameFileExtension(dir.getAbsolutePath() + "/" + fileListString[j], lFileExtensionReverse.get(i));
	                	   
	           			}
	           		catch (Exception e) {}
	       			}
	       		}
		    }
	   }
   }
   
   public void createEmptyPreset() {
	   	   
	   for (int i = 0; i < lPatchCheckboxes300.size(); i++) {
		   
		    if (lPatchCheckboxes300.get(i).isSelected()) {
		        String fileListString[] = dir.list(new extNameFilter(lFileExtension300.get(i)));
	       		if (fileListString != null) {
	       			for (int j=0; j<fileListString.length; j++) {
	       				try {
	       					File file = new File(dir.getAbsolutePath() + "/" + 
	       							fileBaseName(new File(fileListString[j])) +
	       							"." + lFileExtension300Reverse.get(i));
	       				    boolean success = file.createNewFile();
	       					//System.out.println(file);
	       					
	           			}
	       				catch (Exception e) {}
	       			}
	       		}
		    }
	   }
	   
	   for (int i = 0; i < lPatchCheckboxes400.size(); i++) {

		   if (lPatchCheckboxes400.get(i).isSelected()) {
		        String fileListString[] = dir.list(new extNameFilter(lFileExtension400.get(i)));
	      		if (fileListString != null) {
	      			for (int j=0; j<fileListString.length; j++) {
	      				try {
	      					File file = new File(dir.getAbsolutePath() + "/" + 
	       							fileBaseName(new File(fileListString[j])) +
	      							"." + lFileExtension400Reverse.get(i));
	      				    boolean success = file.createNewFile();
	      					//System.out.println(file);
	      					
	          			}
	      				catch (Exception e) {}
	      			}
	      		}
		   }
	   }
	   
   }
   
   public static boolean renameFileExtension(String source, String newExtension) {
     String target;
     String currentExtension = getFileExtension(source);

     if (currentExtension.equals("")){
       target = source + "." + newExtension;
     }
     else {
       target = source.replaceFirst(Pattern.quote("." +
           currentExtension) + "$", Matcher.quoteReplacement("." + newExtension));

     }
     return new File(source).renameTo(new File(target));
   }
   
   public static String getFileExtension(String f) {
     String ext = "";
     int i = f.lastIndexOf('.');
     if (i > 0 &&  i < f.length() - 1) {
       ext = f.substring(i + 1);
     }
     return ext;
   }
   
   public static String fileBaseName(File File) {
		String sWithoutExtension = File.getName();
		int index = sWithoutExtension.lastIndexOf(".");
		if (index != 1)
			sWithoutExtension = sWithoutExtension.substring(0, index);
		return sWithoutExtension;
   }

   
   public void changeText() {
	   int numberPatchesCopy = 0;
	   int numberPatchesRenamed = 0;
	   
	   for (int i = 0; i < lRenameCheckboxes.size(); i++) {
		    if (lRenameCheckboxes.get(i).isSelected()) {
		    	numberPatchesRenamed = numberPatchesRenamed + dir.listFiles(new extFileFilter(lFileExtension.get(i))).length;
		    }
	   }
	   for (int i = 0; i < lPatchCheckboxes.size(); i++) {
		    if (lPatchCheckboxes.get(i).isSelected()) {
		    	numberPatchesCopy = numberPatchesCopy + dir.listFiles(new extFileFilter(lFileExtension.get(i))).length;
		    }
	   }   
       
	   if(chckbxBackup.isSelected() && (chckbxRenameH5e.isSelected() || (chckbxRenameHbe.isSelected())  || (chckbxRenameH5b.isSelected())  || (chckbxRenameHbb.isSelected()) || (chckbxRenameH5s.isSelected()) || (chckbxRenameHbs.isSelected()) )){
		   lblPatchDone.setText("Done: " + numberPatchesCopy + " files patched and " + numberPatchesRenamed + " files renamed. A backup was created");
		   //lblARRNames.setText(numberPatchesRenamed + " files renamed");
	   } else if(chckbxBackup.isSelected() && (chckbxRenameH5e.isSelected() != true || (chckbxRenameHbe.isSelected()) != true || (chckbxRenameH5b.isSelected()) != true || (chckbxRenameHbb.isSelected()) != true || (chckbxRenameH5s.isSelected()) != true || (chckbxRenameHbs.isSelected()) != true )){
		   lblPatchDone.setText("Done: " + numberPatchesCopy + " files patched. A Backup was created");
	   } else if(chckbxBackup.isSelected() != true && (chckbxRenameH5e.isSelected() || (chckbxRenameHbe.isSelected()) || (chckbxRenameH5b.isSelected()) != true || (chckbxRenameHbb.isSelected()) != true || (chckbxRenameH5s.isSelected()) != true || (chckbxRenameHbs.isSelected()) != true  )){
		   lblPatchDone.setText("Done: " + numberPatchesCopy + " files patched and " + numberPatchesRenamed + " files renamed");
		   //lblARRNames.setText(numberPatchesRenamed + " files renamed");
	   } else{
		   lblPatchDone.setText("Done: " + numberPatchesCopy + " files patched");
		   //lblARRNames.setText("");
	   }

   }
   
   public void changeText300() {
	   int numberPatchesCopy = 0;
	   
	   //for (int i = 0; i < lPatchCheckboxes300.size(); i++) {
	   //   if (lPatchCheckboxes300.get(i).isSelected()) {
	   //   	numberPatchesCopy = numberPatchesCopy + dir.listFiles(new extFileFilter(lFileExtension300.get(i))).length / 2;
	   //   }
	   //} 
	   
	   numberPatchesCopy = numberPatchesCopy + dir.listFiles(new extFileFilter(patternH5e)).length;

	   
	   if(chckbxBackup.isSelected()){
		   lbl300PatchDone.setText("Done: " + numberPatchesCopy + " files translated. A Backup was created");
	   } else{
		   lbl300PatchDone.setText("Done: " + numberPatchesCopy + " files translated");
	   }

   }
   
   public class NoneSelectedButtonGroup extends ButtonGroup {

	   @Override
	   public void setSelected(ButtonModel model, boolean selected) {

	     if (selected) {

	       super.setSelected(model, selected);

	     } else {

	       clearSelection();
	     }
	   }
	 }

   static class exitApp implements ActionListener
   {
       public void actionPerformed(ActionEvent e)
       {
           System.exit(0);
       }
   }
}
