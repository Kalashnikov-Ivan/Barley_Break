<h1>Barley Break</h1>

This is consolas game for Linux and Windows.

<p>
  <img src="https://i.ibb.co/Ph2vNVN/2019-09-10-12-32-53.png" width="700" title="start_image">
  <img src="https://i.ibb.co/k1vLN1F/2019-09-10-10-42-14.png" width="700" title="start_image">
</p>
<hr>
<h2>How to install?</h2>
  <h3>Linux</h3>
    <ol>
       <li> From console, clone the repository (or donwload archive from site). 
        <br><code>git clone https://github.com/Kalashnikov-Ivan/Barley_Break.git</code> 
       </li>
       <li> Go to<code>Linux</code>directory.
         <br><code>cd Barley_Break/Linux</code> 
       </li>
       <li> If you don't have <b>ncurses</b> library, run<code>install_ncurses.sh</code>and follow the instructions.
       </li>
       <li> Use<code>make</code>that to build executable file.
       </li>
       <li> After<code>make</code>you get a <code>barleyBreak.elf</code>. Run it and enjoy!
          <br><code>./barleyBreak.elf</code>
       </li>
    </ol>
    <h3>Windows</h3>
      <ol>
        <li> From console, clone the repository (or donwload archive from site).
          <br><code>git clone https://github.com/Kalashnikov-Ivan/Barley_Break.git</code> 
        </li>
        <li> Go to<code>Windows</code>directory.
          <br><code>cd Barley_Break/Windows</code> 
        </li>
        <li> Run <code>Barley_Break.exe</code>. And play!
        </li>
        <li> But... If it don't run, you must to compile it with <b>MVS</b>!
        </li>
        <li> Go to<code>src</code>directory<code>Barley_Break/Windows/src</code>. 
        </li>
        <li> Run <code>Barley_Break.sln</code>and compile the project from MVS in Release.
        </li>
      </ol>
