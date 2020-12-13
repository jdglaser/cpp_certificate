For my comparison, I will go over two different, yet similar C/C++ development environments: Visual Studio and Visual Studio Code.

Visual Studio is Microsofts fully featured IDE. It is very powerful and feature rich, with a lot of add-ons and extensions for different use cases. Since this is a Microsoft product it works very well with .NET development. It also works as a very powerful C/C++ development environment. As you might imagine, it also has a lot of features for developing C/C++ programs for Microsoft environments (Windows PC, Xbox, etc.). That being said, it also has the ability to compile and develop for Linux. One downside of using Visual Studio is how large in size it is. Depending on how many extensions you add in your installation, it is easy to have a Visual Studio installation that is over 20GB in size. This can often make it slow and hard to work with if you don't have a fast computer. Additionally, the learning curve can be quite high, with lots of tinkering with settings before you are ready to actually begin programming.

Visual Studio code is technically just a code editor and not a full IDE. However, by adding certain extensions to VSCode, you can make it work as a regular IDE. Visual studio code is another cross-platform editor by Microsoft. Once you have the C++ extension installed, you can hook it up with your favority compiler of choice on your machine, and begin developing C/C++ programs. It has a very powerful debugger and linting. There are also a lot of really useful extensions that you can install to assist in development of different types of projects. You can easily enable/disable these extensions as needed, so your installation rarely gets to large or slow. Because of this lightweight focus. Visual Studio Code is much lighter than its full IDE counterpart. 

For my C/C++ development, I actually prefer Visual Studio, and have not really found any features missing. I have full git support, debugging support, linting, and build tools that are highly configurable. For example, below is a common `tasks.json` file, which is VSCode's way of defining build tasks.

```
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "shell",
			"label": "g++-9 C++17 build active file",
			"command": "/usr/bin/g++-9",
			"args": [
				"-g",
				"${file}",
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}",
				"-std=c++17"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": "build"
		},
		{
			"type": "shell",
			"label": "g++-9 build active file",
			"command": "/usr/bin/g++-9",
			"args": [
				"-g",
				"${file}",
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": "build"
		},
		{
			"type": "shell",
			"label": "gcc build active file",
			"command": "/usr/bin/gcc",
			"args": [
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}",
				"${file}",
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": "build"
		}
	]
}
```

In the above file, I have several different build configurations set, which I can simply call by pressing `ctrl+shift+b`. I appreciate the simple configuration as code, and lightweight portability of Visual Studio. I'm sure if I was working in a large corporate environment, there'd be some features of Visual Studio that I may need, but for my own personal projects and school work, VSCode is plenty.

**References**

(2020). Develop C and C++ applications. Retrieved from https://visualstudio.microsoft.com/vs/features/cplusplus/

(2020). https://code.visualstudio.com/docs/languages/cpp. Retrieved from https://code.visualstudio.com/docs/languages/cpp