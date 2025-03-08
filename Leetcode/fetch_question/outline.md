Here's the breakdown of your task as a checklist:

### **1. Select LeetCode Problem Based on Difficulty**
- [x] Accept difficulty level parameter from command line (Easy, Medium, Hard) via `argv`.
- [ ] If no parameter is provided, randomize the difficulty.
- [ ] Fetch HTML of the LeetCode problem based on the selected difficulty.

### **2. Create Directory for the Problem**
- [ ] Parse HTML to retrieve the problem title.
- [ ] Extract the acronym for the problem title (e.g., "Longest Repeating Substring" -> "LRS").
- [ ] Create a directory using the acronym as the name.

### **3. Create and Populate `prompt.txt`**
- [ ] Create a `prompt.txt` file inside the newly created directory.
- [ ] Extract and parse the content of the problem's description from the HTML.
- [ ] Dump the parsed problem description into `prompt.txt`.

### **4. Create a tmux Session**
- [ ] Use system commands to create a tmux session.
- [ ] Split the tmux window horizontally.
- [ ] Open a terminal in one pane and a basic project (or editor) in the other.

This checklist covers all the major steps you need to implement.
