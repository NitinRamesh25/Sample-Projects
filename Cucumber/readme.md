# Cucumber JS

### Setting up dependencies

- Install local dependencies. `npm i -s @cucumber/cucumber`

- Add cucumber to package.json
  > "scripts":{
  > "test": "node node_modules/@cucumber/cucumber/bin/cucumber-js"
  > }

### Writing Gherkin speicifications

- Create a "features" directory
- Create a feature file `example_name.feature`
- In the feature file add a `Feature` tag with the value as feature name.
  `Note: Feature name usually matches with the name of the feature file`
- Add a `Scenario` and it's Given, When, Then

### Creating step definitions

- Create step definitions, as Cucumber does not directly know what to do with Gherkin doc.
- Create a "features/step_definitions" directory
- Add .js file containing code for given, when, then.
- When the functionality is yet to be implemented, these functions should return "pending"
- In cmd run `npm test`

### Troubleshooting

##### Cucumber module not found

Add `AppData/Roaming/npm` to **PATH** env variable
Add `AppData/Roaming/npm/node_modules` to **NODE_PATH** env variable
