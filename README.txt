  _____________      _______   _______   _____   _______   
 /            /     |  ___  \ |  ___  \ /  _  \ |  ___  \   
 \  \\\\\\\\\\\\\\  | |___/ / | |___/ / | | | | | |___| /    
  \           ////  | ____  \ |  ___  \ | |_| | |  ____ \    
  /  \\\\\\\\\\\\\  |/    |_| |_|   |_| \_____/ |_|    \|    
  \_           ///\  // ///// /////                 
    \\\\\\\\\\\\\\/  //   =// // //    2014 Code in 2015 BETA
                     // ///// /////      
-------------------------------------------------------------------
--  I. Installation                                              --
-------------------------------------------------------------------

1. If you have not set-up Eclipse, follow the FRC C++ Programming
   guide from FIRST
   https://wpilib.screenstepslive.com/s/4485/m/13810

2. Create a new project from a template.
   [File->New->Project...  WPILib Robot C++ Development->Robot C++ Project]
   Enter a name you want and select "Command-Based Robot"
   Click "Finish".

3. Delete everything in 'src' directory of the newly created project.

4. Clone the Robot-2014 repository into the project.
   Open GitHub GUI client and click "+" sign in the upper left corner.
   Select "Team3130"->"Robot-2014" and click "Clone".
   Find your "workspace" and the directory of the new project.
   Select "src" in that directory and click OK.
   Change the branch to Beta-2015.

5. Go back to Eclipse and "Refresh (F5)" the content of your project.

6. Build.

-------------------------------------------------------------------
--  II. Code Information                                         --
-------------------------------------------------------------------

<No Code Yet>

-------------------------------------------------------------------
--  III. Guidelines for Committing                               --
-------------------------------------------------------------------

1. Commit self-contained changes.  You're not the only one using
   this code.  If you have a single commit that makes a bunch of
   unrelated changes, it's a lot of work to merge.

2. Use descriptive commit information.  Git is tricky, and it's
   much harder when you have to dive into each commit to figure out
   what it's doing.

3. Make branches when appropriate.  If you're making major
   architectural changes to the code, or prototyping a major
   feature that needs testing before it should be integrated into
   production code, make a branch!  Once the branch is considered
   stable, it can be merged with a single commit.  Another use
   case for branches is when testing multiple methods of solving a
   problem: the one method that is chosen can be integrated
   without polluting the codebase with alternatives.

4. <etc.>

-------------------------------------------------------------------
--  IV. Licensing                                                --
-------------------------------------------------------------------

Use this format for code headers for licensing.

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/
