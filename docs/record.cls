\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{record}[2023-10-20 Programs and Output for Record]

\RequirePackage{graphics}
\RequirePackage{graphicx}

\LoadClass[a4paper]{article}

\renewcommand{\normalsize}{\fontsize{12pt}{14pt}\selectfont}
% \setlength{\textwidth}{6.5in}
% \setlength{\textheight}{8in}
\pagenumbering{gobble}

\newenvironment{program}{%
    \textbf{\underline{PROGRAM}} \\
}{
    \pagebreak
}

\newenvironment{programOutput}{%
    \textbf{\underline{OUTPUT}} \\
}{
    \pagebreak
}

\newcommand{\outputImage}[1]{
    \includegraphics{#1}
}