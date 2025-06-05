# Flam_assignment
## SET 1
* I have chosen questions 1, 2 and 4 of set 1
## Question 1
# LRU Cache Implementation

* Data Structure Design: I use a custom Node class with key, value, and bidirectional pointers, along with dummy nodes (left and right) that act as permanent head and tail markers, simplifying insertion and deletion operations by eliminating edge case handling. 
* Hash Map Integration: The unordered_map<int,Node*> provides O(1) key-to-node mapping, while the doubly linked list maintains the usage order with most recently used items near the tail (right) and least recently used near the head (left).
* Movement Strategy: remove_node() and insert_node() helper functions efficiently unlink nodes from their current position and insert them right before the tail sentinel, effectively marking them as most recently used without traversing the entire list.
* Get Operation: When accessing a key, you check the hash map for existence, and if found, move the corresponding node to the tail position to mark it as recently used, then return its value.
* Put Operation: For insertion/update, you handle existing keys by removing the old node, create a new node with the given key-value pair, insert it at the tail, and maintain capacity by evicting the leftmost node (least recently used) when the cache exceeds its size limit.
* Memory Management: You properly delete evicted nodes to prevent memory leaks, though there's a potential bug in your put method where you call delete mp[key] after mp.erase(key), which should be fixed by storing the node pointer before erasing from the map.
* Time Complexity Achievement: All operations run in O(1) time because hash map lookups, doubly linked list insertions/deletions, and node movements are constant time operations, making this an efficient LRU cache implementation.
  
## Question 2
# LRU Cache Implementation
* Data Structure & Hashing: I use a vector of vectors containing key-value pairs (vector<vector<pair<int,int>>> arr) with a fixed table size of 10,000 buckets, and employ simple modulo hashing (key % n) to map keys to bucket indices. 
* Collision Resolution: When multiple keys hash to the same index,I store them in the same bucket using a vector, implementing separate chaining where each bucket can hold multiple key-value pairs.
* Put Operation: I first search the target bucket linearly to check if the key already exists - if found, I update its value; otherwise, you append the new key-value pair to the bucket, ensuring both insertion and updates work correctly. 
* Get Operation: I hash the key to find the appropriate bucket, then perform a linear search through that bucket's vector to find the matching key and return its associated value, or -1 if not found.
* Remove Operation: I locate the target bucket, linearly search for the key, and use vector.erase() to remove the element when found, effectively deleting the key-value pair from the map. 

## Question 4
# Solar System WebGL

## Technical Architecture

```
SolarSystem Class
├── WebGL Context Management
├── Shader Program Management (Sun/Planet/Ring)
├── Geometry Generation (Sphere/Ring)
├── Planetary Data System
├── Matrix Transformations
├── Rendering Pipeline
└── Input Handling
```

## Mathematics Implementation

### Matrix4 Class Operations
```javascript
class Matrix4 {
    perspective(fovy, aspect, near, far)  // Projection matrix
    lookAt(eye, center, up)               // View matrix
    translate(x, y, z)                    // Translation
    rotateX/Y/Z(angle)                    // Rotations
    scale(x, y, z)                        // Scaling
    multiply(matrix)                      // Matrix composition
    getNormalMatrix()                     // 3x3 normal extraction
}
```

### Planetary Data Structure
```javascript
planets = [
    { 
        name: 'Earth', 
        distance: 6,           // Orbital radius
        speed: 1.0,            // Orbital speed multiplier
        size: 0.3,             // Scale factor
        color: [0.42, 0.58, 0.84], // RGB values
        type: 0,               // 0=rocky, 1=gas giant
        moon: true             // Has moon system
    }
]
```

### Transformation Hierarchy
```javascript
// Planet transformation
planetMatrix = Matrix4()
    .translate(cos(angle) * distance, 0, sin(angle) * distance)  // Orbit
    .rotateY(time * speed)                                       // Rotation
    .scale(size, size, size)                                     // Size

// Moon transformation (nested)
moonMatrix = Matrix4()
    .translate(planetX, planetY, planetZ)                        // Follow planet
    .translate(cos(moonAngle) * moonRadius, 0, sin(moonAngle) * moonRadius) // Moon orbit
    .rotateY(time * moonSpeed)                                   // Moon rotation
    .scale(moonSize, moonSize, moonSize)                         // Moon size
```

## Shader Implementation

### Vertex Shader
```glsl
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec2 a_texCoord;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat3 u_normalMatrix;

varying vec3 v_normal;
varying vec3 v_worldPosition;
varying vec2 v_texCoord;

void main() {
    vec4 worldPosition = u_modelMatrix * vec4(a_position, 1.0);
    gl_Position = u_projectionMatrix * u_viewMatrix * worldPosition;
    
    v_normal = normalize(u_normalMatrix * a_normal);
    v_worldPosition = worldPosition.xyz;
    v_texCoord = a_texCoord;
}
```

### Sun Fragment Shader
```glsl
uniform float u_time;
uniform vec3 u_cameraPosition;

// Multi-frequency pulsing
float pulse = 0.85 + 0.15 * sin(u_time * 2.5);
float pulse2 = 0.9 + 0.1 * sin(u_time * 4.0);

// Solar surface activity
float surface1 = sin(v_position.x * 6.0 + u_time) * sin(v_position.y * 6.0 + u_time * 0.7);
float surface2 = cos(v_position.z * 8.0 + u_time * 1.3) * sin(v_position.x * 4.0);
float surfaceActivity = (surface1 + surface2) * 0.15;

// Rim lighting
vec3 viewDir = normalize(u_cameraPosition - v_worldPosition);
float rim = 1.0 - max(0.0, dot(v_normal, viewDir));
rim = pow(rim, 1.5);

vec3 sunColor = vec3(1.0, 0.8, 0.2) * pulse * pulse2;
sunColor += vec3(0.3, 0.1, 0.0) * surfaceActivity * pulse;
sunColor += vec3(1.0, 0.7, 0.3) * rim * pulse * 0.8;
```

### Planet Fragment Shader
```glsl
uniform vec3 u_planetColor;
uniform float u_planetType; // 0=rocky, 1=gas giant

// Phong lighting
vec3 lightDir = normalize(u_lightPosition - v_worldPosition);
vec3 viewDir = normalize(u_cameraPosition - v_worldPosition);
vec3 reflectDir = reflect(-lightDir, v_normal);

vec3 ambient = 0.15 * u_planetColor;
float diff = max(dot(v_normal, lightDir), 0.0);
vec3 diffuse = diff * u_planetColor;

float shininess = u_planetType > 0.5 ? 16.0 : 32.0;
float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
vec3 specular = vec3(0.2 + u_planetType * 0.1) * spec;

// Surface patterns
float pattern;
if (u_planetType > 0.5) {
    // Gas giant bands
    float bands = sin(v_texCoord.y * 15.0 + u_time * 0.1) * 0.1;
    float storms = sin(v_texCoord.x * 8.0 + u_time * 0.3) * sin(v_texCoord.y * 12.0) * 0.05;
    pattern = bands + storms;
} else {
    // Rocky surface
    pattern = sin(v_texCoord.x * 25.0) * sin(v_texCoord.y * 20.0) * 0.08;
}

vec3 color = ambient + diffuse + specular + pattern * u_planetColor;
```

### Ring Fragment Shader
```glsl
uniform float u_innerRadius;
uniform float u_outerRadius;

float distance = length(v_position.xz);

// Ring boundaries
if (distance < u_innerRadius || distance > u_outerRadius) {
    discard;
}

// Ring density patterns
float ringPattern = sin(distance * 50.0) * 0.3 + 0.7;
ringPattern *= sin(distance * 120.0 + u_time) * 0.2 + 0.8;

// Transparency gradient
float alpha = smoothstep(u_innerRadius, u_innerRadius + 0.1, distance) * 
              smoothstep(u_outerRadius, u_outerRadius - 0.1, distance);
alpha *= ringPattern * 0.6;

gl_FragColor = vec4(u_ringColor, alpha);
```

## WebGL Implementation

### Context Setup
```javascript
initGL() {
    const gl = this.gl;
    gl.enable(gl.DEPTH_TEST);
    gl.enable(gl.BLEND);
    gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
    gl.clearColor(0.0, 0.0, 0.05, 1.0);
    
    this.sunProgram = this.createShaderProgram(vertexShaderSource, sunFragmentShaderSource);
    this.planetProgram = this.createShaderProgram(vertexShaderSource, planetFragmentShaderSource);
    this.ringProgram = this.createShaderProgram(vertexShaderSource, ringFragmentShaderSource);
}
```

### Buffer Creation
```javascript
createBuffers(positions, normals, texCoords, indices) {
    const gl = this.gl;
    
    const positionBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
    
    const indexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
    
    return { positionBuffer, normalBuffer, texCoordBuffer, indexBuffer, indexCount: indices.length };
}
```

## Geometry Generation

### Sphere Creation
```javascript
createSphere(radius, widthSegments, heightSegments) {
    const positions = [], normals = [], texCoords = [], indices = [];
    
    for (let i = 0; i <= heightSegments; i++) {
        const theta = i * Math.PI / heightSegments;
        const sinTheta = Math.sin(theta), cosTheta = Math.cos(theta);
        
        for (let j = 0; j <= widthSegments; j++) {
            const phi = j * 2 * Math.PI / widthSegments;
            const sinPhi = Math.sin(phi), cosPhi = Math.cos(phi);
            
            const x = cosPhi * sinTheta;
            const y = cosTheta;
            const z = sinPhi * sinTheta;
            
            positions.push(radius * x, radius * y, radius * z);
            normals.push(x, y, z);
            texCoords.push(j / widthSegments, i / heightSegments);
        }
    }
    
    for (let i = 0; i < heightSegments; i++) {
        for (let j = 0; j < widthSegments; j++) {
            const first = i * (widthSegments + 1) + j;
            const second = first + widthSegments + 1;
            indices.push(first, second, first + 1, second, second + 1, first + 1);
        }
    }
    
    return this.createBuffers(positions, normals, texCoords, indices);
}
```

### Ring Creation
```javascript
createRing(innerRadius, outerRadius, segments) {
    const positions = [], normals = [], texCoords = [], indices = [];
    
    for (let i = 0; i <= segments; i++) {
        const angle = i * 2 * Math.PI / segments;
        const cos = Math.cos(angle), sin = Math.sin(angle);
        
        positions.push(innerRadius * cos, 0, innerRadius * sin);
        positions.push(outerRadius * cos, 0, outerRadius * sin);
        normals.push(0, 1, 0, 0, 1, 0);
        texCoords.push(0, i / segments, 1, i / segments);
    }
    
    for (let i = 0; i < segments; i++) {
        const base = i * 2;
        indices.push(base, base + 1, base + 2, base + 1, base + 3, base + 2);
    }
    
    return this.createBuffers(positions, normals, texCoords, indices);
}
```

## Rendering Pipeline

### Draw Sequence
```javascript
render() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    
    this.updateCamera();
    
    // 1. Draw Sun (opaque)
    this.drawSun();
    
    // 2. Draw Planets (opaque)
    this.planets.forEach((planet, index) => {
        const angle = this.time * planet.speed;
        const planetPosition = this.drawPlanet(planet, angle);
        
        // 3. Draw Moons (opaque)
        if (planet.moon) this.drawMoon(planetPosition, angle);
        if (planet.moons) {
            for (let i = 0; i < planet.moons; i++) {
                this.drawMoon(planetPosition, angle, i);
            }
        }
        
        // 4. Draw Rings (transparent - last)
        if (planet.rings) this.drawRings(planetPosition);
    });
}
```

### Uniform Management
```javascript
setupUniforms(program, modelMatrix) {
    const projectionMatrix = new Matrix4().perspective(Math.PI/4, this.canvas.width/this.canvas.height, 0.1, 200);
    const viewMatrix = new Matrix4().lookAt(this.camera.position, [0, 0, 0], [0, 1, 0]);
    
    gl.uniformMatrix4fv(gl.getUniformLocation(program, 'u_modelMatrix'), false, modelMatrix.elements);
    gl.uniformMatrix4fv(gl.getUniformLocation(program, 'u_viewMatrix'), false, viewMatrix.elements);
    gl.uniformMatrix4fv(gl.getUniformLocation(program, 'u_projectionMatrix'), false, projectionMatrix.elements);
    gl.uniformMatrix3fv(gl.getUniformLocation(program, 'u_normalMatrix'), false, modelMatrix.getNormalMatrix());
}
```

## Input System

### Camera Control
```javascript
updateCamera() {
    const x = this.camera.distance * Math.cos(this.camera.rotation.x) * Math.sin(this.camera.rotation.y);
    const y = this.camera.distance * Math.sin(this.camera.rotation.x);
    const z = this.camera.distance * Math.cos(this.camera.rotation.x) * Math.cos(this.camera.rotation.y);
    this.camera.position = [x, y, z];
}

handleMouseMove(event) {
    if (!this.mouse.isDown) return;
    
    const deltaX = event.clientX - this.mouse.lastX;
    const deltaY = event.clientY - this.mouse.lastY;
    
    this.camera.rotation.y += deltaX * 0.01;
    this.camera.rotation.x += deltaY * 0.01;
    this.camera.rotation.x = Math.max(-Math.PI/2, Math.min(Math.PI/2, this.camera.rotation.x));
}
```

## Performance Optimization

### Efficient Rendering
```javascript
// Shared geometry for all spheres
this.sphere = this.createSphere(1, 32, 16);  // Created once, scaled per object

// Minimal shader switching
render() {
    gl.useProgram(this.sunProgram);     // Sun
    // ... draw sun
    
    gl.useProgram(this.planetProgram);  // All planets and moons
    // ... draw all planets and moons
    
    gl.useProgram(this.ringProgram);    // Rings only
    // ... draw rings
}

// Batch uniform updates
setupAttributes(geometry) {
    gl.bindBuffer(gl.ARRAY_BUFFER, geometry.positionBuffer);
    gl.vertexAttribPointer(0, 3, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, geometry.indexBuffer);
}
```
