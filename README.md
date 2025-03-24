# JSON Plugin Documentation

## Overview

The JSON Plugin is a visualization tool for displaying system tree data in JSON format. It integrates with Cube, a performance analysis framework, and provides an interactive tab to visualize system tree data.

## Features

- Displays system tree data in JSON format.

- Supports hierarchical tree structures.

- Provides a scrollable interface for viewing JSON output.

- Automatically updates when a tree item is selected.

## Installation

- Ensure that Cube is installed on your system.

- Compile the plugin using the same Qt and compiler version as Cube.

- Place the compiled plugin in the Cube plugin directory.

## Usage

- Open Cube and navigate to the JSON Plugin tab.

- Select a tree item to display its JSON representation.

- The JSON output will be updated dynamically in the plugin interface.

## Code Structure

### Main Components

- JSONPlugin (Class): Implements Cube plugin and tab interface.

- cubeOpened(): Initializes the plugin and UI components.

- cubeClosed(): Cleans up resources when the plugin is closed.

- treeItemIsSelected(): Handles tree item selection events and generates JSON.

- getJSONData(): Recursively constructs a JSON object from the tree structure.

### UI Components

- QLabel: Displays the JSON output.

- QVBoxLayout: Manages layout for the plugin UI.

- QScrollArea: Enables scrolling for large JSON outputs.

- QWidget: Main Widget for the plugin and content
