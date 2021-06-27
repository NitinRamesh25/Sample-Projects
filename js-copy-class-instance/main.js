// class Project {
//   constructor({ project_name = "", chiller_options = [] }) {
//     this.project_name = project_name;
//     this.chiller_options = chiller_options;
//   }

//   clone() {
//     const new_chillers = [];
//     this.chiller_options.forEach((chiller) => {
//       new_chillers.push(chiller.clone());
//     });

//     const obj = new Project({ ...this, chiller_options: new_chillers });
//     return obj;
//   }
// }

// class ChillerOption {
//   constructor({ chiller_type }) {
//     this.chiller_type = chiller_type;
//   }

//   clone() {
//     const obj = new ChillerOption({ ...this });
//     return obj;
//   }
// }

// const chiller1 = new ChillerOption({ chiller_type: "type1" });

// const proj1 = new Project({
//   project_name: "project1",
//   chiller_options: [chiller1],
// });

// const proj2 = proj1.clone();
// proj2.chiller_options[0].chiller_type = "type2";

// console.log(proj1);
// console.log(proj2);

const obj = {
  callback: () => 10,
};
