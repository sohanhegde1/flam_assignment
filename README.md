# Flam_assignment
## SET 1
* I have chosen questions 1,2 and 3 of set1
## Question 1

* Data Structure Design: I use a custom Node class with key, value, and bidirectional pointers, along with dummy nodes (left and right) that act as permanent head and tail markers, simplifying insertion and deletion operations by eliminating edge case handling. 
* Hash Map Integration: The unordered_map<int,Node*> provides O(1) key-to-node mapping, while the doubly linked list maintains the usage order with most recently used items near the tail (right) and least recently used near the head (left).
* Movement Strategy: remove_node() and insert_node() helper functions efficiently unlink nodes from their current position and insert them right before the tail sentinel, effectively marking them as most recently used without traversing the entire list.
* Get Operation: When accessing a key, you check the hash map for existence, and if found, move the corresponding node to the tail position to mark it as recently used, then return its value.
* Put Operation: For insertion/update, you handle existing keys by removing the old node, create a new node with the given key-value pair, insert it at the tail, and maintain capacity by evicting the leftmost node (least recently used) when the cache exceeds its size limit.
* Memory Management: You properly delete evicted nodes to prevent memory leaks, though there's a potential bug in your put method where you call delete mp[key] after mp.erase(key), which should be fixed by storing the node pointer before erasing from the map.
* Time Complexity Achievement: All operations run in O(1) time because hash map lookups, doubly linked list insertions/deletions, and node movements are constant time operations, making this an efficient LRU cache implementation.
## Question 2
* Data Structure & Hashing: I use a vector of vectors containing key-value pairs (vector<vector<pair<int,int>>> arr) with a fixed table size of 10,000 buckets, and employ simple modulo hashing (key % n) to map keys to bucket indices. 
* Collision Resolution: When multiple keys hash to the same index,I store them in the same bucket using a vector, implementing separate chaining where each bucket can hold multiple key-value pairs.
* Put Operation: I first search the target bucket linearly to check if the key already exists - if found, I update its value; otherwise, you append the new key-value pair to the bucket, ensuring both insertion and updates work correctly. 
* Get Operation: I hash the key to find the appropriate bucket, then perform a linear search through that bucket's vector to find the matching key and return its associated value, or -1 if not found.
* Remove Operation: I locate the target bucket, linearly search for the key, and use vector.erase() to remove the element when found, effectively deleting the key-value pair from the map. 

## Question 4
# Solar System WebGL Visualization

A comprehensive 3D solar system simulation built with pure WebGL, demonstrating advanced graphics programming concepts including custom shaders, matrix transformations, and interactive camera controls.

![Solar System Demo](https://via.placeholder.com/800x400/000033/ffffff?text=Interactive+Solar+System+WebGL)

## 🌟 Features

### Visual Elements
- **☀️ Animated Sun** with pulsing glow and rim lighting effects
- **🌍 Earth** with realistic orbital mechanics and axial rotation
- **🌙 Moon** orbiting Earth with nested transformations
- **🔴 Mars** with independent orbital characteristics
- **Real-time lighting** with Phong shading model
- **Smooth animations** running at 30+ FPS

### Interactive Controls
- **Mouse drag** to rotate camera around the solar system
- **Mouse scroll** to zoom in/out (5-50 unit range)
- **Touch support** for mobile devices
- **Constrained camera** preventing gimbal lock

### Technical Features
- **Custom GLSL shaders** for realistic rendering
- **Efficient WebGL rendering** with VBOs/VAOs
- **Matrix transformation pipeline** for 3D positioning
- **Real-time FPS monitoring**
- **Responsive design** adapting to any screen size

## 🏗️ Technical Architecture

### Core Components

```
SolarSystem Class
├── WebGL Context Management
├── Shader Program Creation
├── Geometry Generation
├── Matrix Mathematics
├── Camera System
├── Input Handling
└── Render Loop
```

### Rendering Pipeline

```
Vertex Shader → Primitive Assembly → Rasterization → Fragment Shader → Frame Buffer
```

## 📐 Mathematics Implementation

### Custom Matrix4 Class

The project implements a complete 4x4 matrix library from scratch:

```javascript
class Matrix4 {
    // Core operations
    identity()           // Reset to identity matrix
    perspective()        // Create projection matrix
    lookAt()            // Create view matrix
    translate()         // Translation transformation
    rotateX/Y()         // Rotation transformations
    scale()             // Scale transformation
    multiply()          // Matrix multiplication
    getNormalMatrix()   // Extract 3x3 normal matrix
}
```

### Transformation Hierarchy

```
World Space
├── Sun (static at origin)
├── Earth
│   ├── Orbital transformation (around Sun)
│   ├── Rotational transformation (self-rotation)
│   └── Moon
│       ├── Earth-relative orbital transformation
│       └── Self-rotation
└── Mars
    ├── Orbital transformation (around Sun)
    └── Rotational transformation (self-rotation)
```

## 🎨 Shader Programming

### Vertex Shader Architecture

```glsl
// Input attributes from VBOs
attribute vec3 a_position;    // Vertex positions
attribute vec3 a_normal;      // Surface normals
attribute vec2 a_texCoord;    // Texture coordinates

// Transformation matrices
uniform mat4 u_modelMatrix;      // Object to world space
uniform mat4 u_viewMatrix;       // World to camera space
uniform mat4 u_projectionMatrix; // Camera to clip space
uniform mat3 u_normalMatrix;     // Normal transformation

// Output to fragment shader
varying vec3 v_normal;        // Interpolated normals
varying vec3 v_position;      // World position
varying vec2 v_texCoord;      // Texture coordinates
varying vec3 v_worldPosition; // World space position
```

### Fragment Shader Techniques

#### Sun Shader (Advanced Effects)
```glsl
// Time-based pulsing effect
float pulse = 0.8 + 0.2 * sin(u_time * 3.0);

// Procedural surface detail
float surface = sin(v_position.x * 8.0) * sin(v_position.y * 8.0) * sin(v_position.z * 8.0);

// Rim lighting for glow effect
vec3 viewDir = normalize(u_cameraPosition - v_worldPosition);
float rim = 1.0 - max(0.0, dot(v_normal, viewDir));
rim = pow(rim, 2.0);  // Sharper falloff
```

#### Planet Shader (Phong Lighting)
```glsl
// Phong lighting model components
vec3 ambient = 0.1 * u_planetColor;                    // Ambient lighting
float diff = max(dot(v_normal, lightDir), 0.0);        // Diffuse component
vec3 diffuse = diff * u_planetColor;                   // Diffuse lighting
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // Specular highlight
vec3 specular = vec3(0.3) * spec;                      // Specular component

// Procedural surface patterns
float pattern = sin(v_texCoord.x * 20.0) * sin(v_texCoord.y * 15.0) * 0.1;
```

## 🔧 WebGL Implementation Details

### Buffer Management

The application uses efficient buffer objects for geometry data:

```javascript
// Vertex Buffer Object (VBO) creation
const positionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

// Element Buffer Object (EBO) for indexed rendering
const indexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
```

### Sphere Geometry Generation

Procedural sphere creation using parametric equations:

```javascript
// Parametric sphere generation
for (let i = 0; i <= heightSegments; i++) {
    const theta = i * Math.PI / heightSegments;        // Latitude angle
    for (let j = 0; j <= widthSegments; j++) {
        const phi = j * 2 * Math.PI / widthSegments;   // Longitude angle
        
        // Spherical to Cartesian coordinates
        const x = cosPhi * sinTheta;
        const y = cosTheta;
        const z = sinPhi * sinTheta;
        
        positions.push(radius * x, radius * y, radius * z);
        normals.push(x, y, z);  // Normalized surface normals
        texCoords.push(j / widthSegments, i / heightSegments);
    }
}
```

**Topology**: 32 width segments × 16 height segments = 512 vertices per sphere
**Optimization**: Shared vertices with indexed rendering reduces redundancy

## 🎮 Input System

### Mouse/Touch Event Handling

```javascript
// Unified input handling for mouse and touch
canvas.addEventListener('mousedown', startInteraction);
canvas.addEventListener('touchstart', startInteraction);

function startInteraction(event) {
    mouse.isDown = true;
    const clientX = event.clientX || event.touches[0].clientX;
    const clientY = event.clientY || event.touches[0].clientY;
    mouse.lastX = clientX;
    mouse.lastY = clientY;
}
```

### Camera Control System

```javascript
// Spherical camera positioning
updateCamera() {
    const x = distance * cos(rotX) * sin(rotY);
    const y = distance * sin(rotX);
    const z = distance * cos(rotX) * cos(rotY);
    camera.position = [x, y, z];
}

// Constraint system
camera.rotation.x = Math.max(-PI/2, Math.min(PI/2, camera.rotation.x)); // Pitch limit
camera.distance = Math.max(5, Math.min(50, camera.distance));           // Zoom bounds
```

## 🚀 Performance Optimizations

### Rendering Efficiency
- **Static Geometry**: Sphere buffers created once, reused for all objects
- **Shader Switching**: Minimal program changes (Sun vs Planet shaders)
- **Uniform Caching**: Efficient uniform location retrieval
- **Index Rendering**: `drawElements()` reduces vertex processing

### Memory Management
- **Float32Array**: Typed arrays for optimal GPU transfer
- **Buffer Reuse**: Single sphere geometry for all celestial bodies
- **Matrix Pooling**: Efficient matrix operations without excessive allocation

### Frame Rate Optimization
```javascript
// Efficient animation loop
requestAnimationFrame(() => this.animate());

// FPS monitoring without performance impact
if (this.fpsCounter % 60 === 0) {
    const fps = Math.round(1000 / deltaTime);
    updateFPSDisplay(fps);
}
```

## 🎯 Orbital Mechanics

### Realistic Planetary Motion

```javascript
// Earth orbital parameters
const earthOrbitRadius = 4.0;     // Distance from Sun
const earthOrbitSpeed = 0.5;      // Angular velocity
const earthRotationSpeed = 2.0;   // Axial rotation

// Time-based animation
const earthAngle = time * earthOrbitSpeed;
const earthMatrix = new Matrix4()
    .translate(cos(earthAngle) * earthOrbitRadius, 0, sin(earthAngle) * earthOrbitRadius)
    .rotateY(time * earthRotationSpeed)
    .scale(0.5, 0.5, 0.5);
```

### Nested Orbital System (Earth-Moon)

```javascript
// Moon orbit relative to Earth's position
const moonMatrix = new Matrix4()
    .translate(earthX, earthY, earthZ)                    // Follow Earth
    .translate(cos(moonAngle) * moonRadius, 0, sin(moonAngle) * moonRadius) // Moon orbit
    .rotateY(time * moonRotationSpeed)                    // Moon rotation
    .scale(0.15, 0.15, 0.15);                            // Moon size
```

## 🌐 Browser Compatibility

### WebGL Support
- **Chrome/Edge**: Full support (WebGL 1.0/2.0)
- **Firefox**: Full support (WebGL 1.0/2.0)
- **Safari**: Full support (WebGL 1.0)
- **Mobile**: iOS Safari, Chrome Mobile, Firefox Mobile

### Feature Detection
```javascript
const gl = canvas.getContext('webgl') || canvas.getContext('experimental-webgl');
if (!gl) {
    alert('WebGL not supported');
    return;
}
```

### Progressive Enhancement
- Graceful fallback for unsupported browsers
- Touch event handling for mobile devices
- Responsive canvas sizing for all screen sizes



### Controls
- **Rotate**: Click and drag (or touch and drag on mobile)
- **Zoom**: Mouse wheel (or pinch gesture on mobile)
- **Reset**: Refresh the page

## 📁 Code Structure

```
solar-system.html
├── HTML Structure
│   ├── Canvas element
│   ├── Control information overlay
│   └── FPS counter display
├── CSS Styling
│   ├── Full-screen layout
│   ├── Cursor states
│   └── Overlay positioning
└── JavaScript Implementation
    ├── Shader source code (GLSL)
    ├── Matrix4 mathematics library
    ├── SolarSystem main class
    ├── Geometry generation
    ├── Input handling
    ├── Rendering pipeline
    └── Animation loop
```





---

**Built with**: Pure WebGL, GLSL, JavaScript ES6+, HTML5 Canvas
**Performance**: 30+ FPS on modern devices
**Compatibility**: All WebGL-capable browsers
