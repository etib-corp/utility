/*
** ETIB PROJECT, 2026
** xider
** File description:
** model
*/

#pragma once

#include <sstream>
#include <filesystem>
#include <istream>
#include <iostream>

#include <tiny_obj_loader.h>

#include <utility/system_io/file.hpp>

#include <utility/graphic/renderable.hpp>
#include <utility/graphic/size.hpp>

#include <utility/logging/loggable.hpp>
#include <utility/logging/default_logger.hpp>

namespace utility::graphic
{
	/**
	 * @class Model
	 * @brief The Model class represents a 3D model in the graphics application.
	 *
	 * The Model class is responsible for storing the data and properties of a
	 * 3D model, including its vertices, textures, materials, and other relevant
	 * information. It provides methods to load and manage the model's data,
	 * allowing for efficient rendering and manipulation within the graphics
	 * application.
	 */
	class Model:
		public Renderable,
		protected utility::logging::Loggable<Model,
											 utility::logging::DefaultLogger>
	{
		public:
		/**
		 * @enum ModelType
		 * @brief The ModelType enum represents the different types of 3D models
		 * that can be loaded and rendered in the graphics application. It
		 * currently includes OBJ, FBX, and GLTF model formats, allowing for
		 * flexibility in the types of models that can be used within the
		 * application. Additional model types can be added to this enum as
		 * needed to support more formats in the future.
		 */
		enum class ModelType {
			OBJ,
			FBX,	 // Not implemented yet
			GLTF,	 // Not implemented yet
					 // Add more model types as needed
		};

		/**
		 * @brief Constructs a Model object from a given File containing the
		 * model data.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * model data to be loaded. This constructor is responsible for
		 * initializing the Model object by loading the model data from the
		 * provided File. It processes the model data and populates the
		 * necessary properties of the Model object, such as vertices, textures,
		 * and materials, based on the content of the File.
		 * @param pose The initial position and orientation for the model.
		 * @param materialID The ID of the material associated with the model.
		 *
		 * @note This implementation will parse the model according to the
		 * extensions of the file (e.g., .obj, .fbx, .gltf) and set the
		 * appropriate ModelType based on the file format.
		 */
		Model(std::shared_ptr<utility::File> modelAsset, const PoseF &pose, uint32_t materialID);

		/**
		 * @brief Constructs a Model object from a given File containing the
		 * model data and a specified ModelType.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * model data to be loaded.
		 * @param type The type of the model (e.g., OBJ, FBX, GLTF) to be
		 * loaded.
		 * @param pose The initial position and orientation for the model.
		 * @param materialID The ID of the material associated with the model.
		 *
		 * This constructor is responsible for initializing the Model object by
		 * loading the model data from the provided File and setting the
		 * ModelType based on the specified type parameter.
		 */
		Model(std::shared_ptr<utility::File> modelAsset, ModelType type,
			  const PoseF &pose,
			  uint32_t materialID);

		/**
		 * @brief Destructs the Model object, releasing any allocated resources.
		 */
		~Model() = default;

		/**
		 * @brief Get the type of the model.
		 *
		 * @return The ModelType enum value representing the type of the model
		 * (e.g., OBJ, FBX, GLTF).
		 */
		[[nodiscard]] ModelType type() const;

		/**
		 * @brief Computes the bounding size of the model.
		 *
		 * @return The bounding size of the model.
		 */
		utility::graphic::SizeF computeBoundingSize(void);

		/**
		 * @brief Get the material ID associated with the model.
		 *
		 * @return The material ID as a uint32_t value.
		 */
		uint32_t getMaterialID(void) const;

		protected:
		/**
		 * @brief Loads a model from a given File containing the model data.
		 *
		 * @param modelAsset A shared pointer to the File object containing the
		 * model data to be loaded.
		 *
		 * This method is responsible for parsing the model data from the
		 * provided File and populating the necessary properties of the Model
		 * object, such as vertices, textures, and materials, based on the
		 * content of the File. The parsing process will depend on the format of
		 * the model data (e.g., OBJ, FBX, GLTF) and will set the appropriate
		 * ModelType based on the file format.
		 * @note This method is called internally by the constructors to load
		 * the model data when a Model object is created.
		 */
		void loadOBJ(std::shared_ptr<utility::File> modelAsset);

		ModelType _type;	///< The type of the model (e.g., OBJ, FBX, GLTF)
		utility::graphic::SizeF
			_boundingBox {};	///< The bounding box of the model

		uint32_t _materialID;	 ///< The material associated with the model

		using Loggable::getLogger;
	};
}	 // namespace utility::graphic
