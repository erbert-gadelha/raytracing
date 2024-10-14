const btn_sphere = document.querySelector("#btn-add-sphere"),
  btn_plane = document.querySelector("#btn-add-plane"),
  btn_light = document.querySelector("#btn-add-light");

btn_sphere.addEventListener("click", () => addObject("Esfera"));
btn_plane.addEventListener("click", () => addObject("Plano"));
btn_light.addEventListener("click", () => addObject("Luz"));

const objects = {
  count: 0,
  elements: {
    "camera": document.querySelector("#object-camera"),
    "ambiental": document.querySelector("#object-ambiental")
  }
};

const container = document.querySelector("#container");




function addObject(objectName) {
  const object = createObjectElement(objectName);  
  objects.elements[objects.count] = object;
  container.appendChild(object);
  objects.count++;
}

function createObjectElement(objectName) {
  const object = document.createElement('div');
  object.classList.add('object');
  
  switch(objectName) {
    case 'Plano': object.classList.add('plane'); break;
    case 'Esfera': object.classList.add('sphere'); break;
    case 'Luz': object.classList.add('light'); break;
  }
  
  object.appendChild(createObjectTitle(objectName));
  object.innerHTML += createObjectVectorsAsString(objectName);
  object.innerHTML += createObjectUniqueAsString(objectName);
  
  const btnDelete = document.createElement('button');
  btnDelete.classList.add('material-symbols-outlined');
  btnDelete.classList.add('btn-remove');
  btnDelete.innerHTML = 'close';
  object.appendChild(btnDelete);
  
  
  const objectId = objects.count;
  btnDelete.addEventListener('click', () => {removeObject(objectId);});
  
  
  return object;
}

function createObjectTitle(objectName) {
  const object = document.createElement('div');
  object.classList.add('object-title');
  
  let symbol = '';
  
  switch(objectName) {
    case 'Plano': symbol = 'background_grid_small'; break;
    case 'Esfera': symbol = 'radio_button_unchecked'; break;
    case 'Luz': symbol = 'wb_incandescent'; break;
  }
  
  object.innerHTML = `
      <span class="material-symbols-outlined"> ${symbol} </span>
      <span id="object-title"> ${objectName} </span>`;
  
  return object;
}

function createObjectVectorsAsString(objectName) {
  let rotString = '';  
  
  if(objectName == 'Plano') {
    rotString = `<span class="param-rot label"> vetor normal </span>
    <div class="param-rot input param-vector">
      <span>x:</span>
      <input id="rot-x" type="number" value="0" step=".5" max="100" min="-100">
      <span>y:</span>
      <input id="rot-y" type="number" value="1" step=".5" max="100" min="-100">
      <span>z:</span>
      <input id="rot-z" type="number" value="0" step=".5" max="100" min="-100">
    </div>`;
  }
  
  
  const cordString = `<span class="param-cord label"> cordenada </span>
    <div class="param-cord input param-vector">
      <span>x:</span>
      <input id="cord-x" type="number" value="0" step=".5" max="100" min="-100">
      <span>y:</span>
      <input id="cord-y" type="number" value="0" step=".5" max="100" min="-100">
      <span>z:</span>
      <input id="cord-z" type="number" value="0" step=".5" max="100" min="-100">
    </div>`;
  
  return cordString + rotString;
}

function createObjectUniqueAsString(objectName) {
  let label = '';
  let color = '#FFFFFF'
  
  switch(objectName) {
    case 'Plano': color = '#5555FF'; break;
    case 'Esfera': label = 'raio'; color = '#FF5555'; break;
    case 'Luz': label = 'intensidade'; color = '#FFFA75';break;
  }
  
  let paramUnique = '';
  
  
  
  if(objectName == 'Esfera' || objectName == 'Luz') {
    paramUnique = `
    <span class="param-unique label"> ${label} </span>
    <input id="input-unique" class="param-unique input" type="number" value="1" step=".1" max="100" min="0.01">`;
  }
  
  
  let paramColor = `<span class="param-color label"> color </span>
    <input id="input-color" class="param-color input" type="color" value="${color}">`;
  

  return paramUnique + paramColor;
}

function removeObject(objectId) {
  const element = objects.elements[objectId];
  if(element != null) {
    element.remove();  
    delete objects.elements[objectId];
  } else {
    console.warn('Element not found.');
  }
}




document.querySelector("#btn-submit").addEventListener('click',() => {
  
  
  const keys = Object.keys(objects.elements);
  const objectsAttributes = [];
  
  for(let i = 0; i < keys.length; i++) {
      objectsAttributes.push({
      "#cord-x": null,
      "#cord-y": null,
      "#cord-z": null,
      "#rot-x": null,
      "#rot-y": null,
      "#rot-z": null,
      "#input-unique": null,
      "#input-color": null,
    });
  }
  
  for(let i = 0; i < keys.length; i++) {
    const element = objects.elements[keys[i]];
    const attributes = objectsAttributes[i];   
    
    for(const attribute in attributes) {
      const attributeElement = element.querySelector(attribute);      
      if(attributeElement) {
        const attributeValue = attributeElement.value;
        if(attribute == '#input-color')
          attributes[attribute] = attributeValue;
        else
          attributes[attribute] = Number(attributeValue);        
      } else {
        delete attributes[attribute];
      }
    }
    
    attributes['type'] = element.querySelector("#object-title").innerHTML.trim();
  };
  
  
  const hexToRgb = (hex) => {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result ? {
      r: parseInt(result[1], 16),
      g: parseInt(result[2], 16),
      b: parseInt(result[3], 16)
    } : null;
  }

  
  let result = "\n";
  
  for(let i = 0; i < objectsAttributes.length; i++) {
    const obj = objectsAttributes[i];
    const color = hexToRgb( obj['#input-color'] );
    
    
    let str = "";
    
    switch(obj['type']) {
      // CAMERA_OBJECT
      case 'Camera': str = `Camera (${obj['#input-unique']}) (${obj['#rot-x']} ${obj['#rot-y']} ${obj['#rot-z']}) (${obj['#cord-x']} ${obj['#cord-y']} ${obj['#cord-z']})`; break;
      
      // AMBIENTAL_OBJECT
      case 'Ambiental': str = `Ambiental (${color.r} ${color.g} ${color.b}) (${obj['#input-unique']})`; break;
      
      // PLANE_OBJECT
      case 'Plano': str = `Plano (${obj['#cord-x']} ${obj['#cord-y']} ${obj['#cord-z']}) (${obj['#rot-x']} ${obj['#rot-y']} ${obj['#rot-z']}) (${color.r} ${color.g} ${color.b}) (1 0.1 1 1 1 1 1 1)`; break;
                
      // SPHERE_OBJECT
      case 'Esfera': str = `Esfera (${obj['#input-unique']}) (${obj['#cord-x']} ${obj['#cord-y']} ${obj['#cord-z']}) (${color.r} ${color.g} ${color.b}) (1 0.1 1 1 1 1 1 1)`; break;
      
      // LIGHT_OBJECT
      case 'Luz': str = `Luz (${obj['#cord-x']} ${obj['#cord-y']} ${obj['#cord-z']}) (${color.r} ${color.g} ${color.b}) (${obj['#input-unique']})`; break;
        
    }
    result += str + '\n';
  }
  

  //console.log(result);
  const ppm = RenderScene(result);
  RenderCanvas(ppm);
});


function RenderScene(scene_description) {
    //const scene_description = "Camera (128) (5 0 0) (0 2 -10)\nAmbiental (255 255 255) (0.2)\nLuz (-5 1 -1) (255 255 255) (1)\n\nEsfera (1) (0 .35 0) (255 0 0) (1 0.1 1 1 1 1 1 1)\nEsfera (0.2) (-1.2 .5 0) (255 255 0) (1 2 0.8 1 1 10 1 1)\nEsfera (0.4) (1.5 1 1) (0 255 0) (1 0.1 1 1 1 1 1 1)\nEsfera (1) (-0.35 1.7 0.2) (255 0 0) (1 2 0.1 1 1 100 1 1)\nEsfera (1) (1 2 0.2) (0 0 0) (0.3 0.4 0.1 0.1 1 100 0.1 10.8)\n\nPlano (0 0 0) (0 1 0) (255 255 0) (1 0.1 1 1 1 1 1 1)";


    const result = Module.ccall(
    "Render", // name of C function
    "number", // return type
    ["string"], // argument types
    [scene_description], // arguments
    );

    return Module.UTF8ToString(result);
}


//document.getElementById('renderButton').addEventListener('click', function() {
function RenderCanvas(ppm) {
    //const text = document.getElementById('inputText').value;
    const lines = ppm.split('\n');

    let width, height, maxVal;
    let headerEnded = false;
    let pixelData = [];
    let headerLines = 0;

    // Parse the header
    for (let i = 0; i < lines.length; i++) {
        const line = lines[i].trim();
        if (line.startsWith('#')) continue; // Ignore comments
        if (line === 'P3') continue; // Ignore magic number (P3 for ASCII PPM)

        if (!headerEnded) {
            if (headerLines === 0) {
                // Get width and height
                [width, height] = line.split(' ').map(Number);
                headerLines++;
            } else if (headerLines === 1) {
                // Get max value
                maxVal = Number(line);
                headerEnded = true;
            }
            continue;
        }

        // After header, collect pixel data
        pixelData.push(...line.split(' ').map(Number));
    }

    // Create a Canvas and draw the image
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    canvas.width = width;
    canvas.height = height;

    const imageData = ctx.createImageData(width, height);
    const data = imageData.data;

    // Fill the canvas pixel data with the PPM values
    for (let i = 0, j = 0; i < pixelData.length; i += 3, j += 4) {
        data[j] = pixelData[i];       // Red
        data[j + 1] = pixelData[i + 1]; // Green
        data[j + 2] = pixelData[i + 2]; // Blue
        data[j + 3] = 255;            // Alpha (fully opaque)
    }

    ctx.putImageData(imageData, 0, 0);
}

