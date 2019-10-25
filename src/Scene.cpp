#include "Scene.h"

#include "Scene.h"
#include <fstream>
#include "ShaderEyelight.h"
#include "ShaderPhong.h"

#include "PrimTriangle.h"
#include "PrimSphere.h"


void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	// --- PUT YOUR CODE HERE ---
	std::vector<Vec3f> vertices;

	std::vector<int> fix;
	std::vector<int> fiy;
	std::vector<int> fiz;

	std::string line;
	std::ifstream file;

	file.open(fileName);

	if(!file.is_open()){
		std::cout << fileName << " can't be opened" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::getline(file,line);
	while(!file.eof()){
		if(line.substr(0, 1) == "f"){
    		std::istringstream components(line.substr(2));

    		int x;
				int y;
				int z;

        components >> x;
				components >> y;
				components >> z;

				fix.push_back(x);
				fiy.push_back(y);
				fiz.push_back(z);
			}

		else if(line.substr(0, 1) == "v"){
    		std::istringstream components(line.substr(2));

    		double dx;
				double dy;
				double dz;

				components >> dx;
				components >> dy;
				components >> dz;

        vertices.push_back(Vec3f(dx,dy,dz) * 100);
			}
			std::getline(file,line);
		}

	for(int i = 0; i < fix.size(); i++){
		Vec3f x = vertices[fix[i] - 1];
		Vec3f y = vertices[fiy[i] - 1];
		Vec3f z = vertices[fiz[i] - 1];
		Add(std::make_shared<CPrimTriangle>(x, y, z, pShader));
	}
	std::cout << "Finished Parsing" << std::endl;
}
